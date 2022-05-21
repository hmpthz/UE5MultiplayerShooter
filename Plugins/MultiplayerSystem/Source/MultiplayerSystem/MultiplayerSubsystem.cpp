#include "MultiplayerSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


UMultiplayerSubsystem::UMultiplayerSubsystem() :
    InternalCreateSessionComplete(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::CreateSessionCompleteCallback)),
    InternalFindSessionsComplete(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::FindSessionsCompleteCallback)),
    InternalJoinSessionComplete(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::JoinSessionCompleteCallback)),
    InternalStartSessionComplete(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::StartSessionCompleteCallback)),
    InternalDestroySessionComplete(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::DestroySessionCompleteCallback))
{
    bCreateSessionOnDestroy = false;
    DesiredNumPublicConnections = 4;
    DesiredMatchType = FString(TEXT("FreeShooting"));

    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        SessionInterface = Subsystem->GetSessionInterface();

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue,
                FString::Printf(TEXT("Online Subsystem: %s"), *Subsystem->GetSubsystemName().ToString()));
        }
    }
}

void UMultiplayerSubsystem::CreateSession(int32 NumPublicConnections, FString MatchType)
{
    DesiredNumPublicConnections = NumPublicConnections;
    DesiredMatchType = MatchType;
    if (!SessionInterface.IsValid())
    {
        return;
    }

    auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
    if (ExistingSession)
    {
        bCreateSessionOnDestroy = true;
        LastNumPublicConnections = NumPublicConnections;
        LastMatchType = MatchType;

        DestroySession();
        return;
    }

    // Store the delegate in a FDelegateHandle so we can later remove it from the delegate list
    InternalCreateSessionCompleteHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(InternalCreateSessionComplete);

    LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
    LastSessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
    LastSessionSettings->NumPublicConnections = NumPublicConnections;
    LastSessionSettings->bAllowJoinInProgress = true;
    LastSessionSettings->bAllowJoinViaPresence = true;
    LastSessionSettings->bShouldAdvertise = true;
    LastSessionSettings->bUsesPresence = true;
    LastSessionSettings->Set(FName("MatchType"), MatchType, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    LastSessionSettings->BuildUniqueId = 1;
    LastSessionSettings->bUseLobbiesIfAvailable = true;

    const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
    if (!SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(InternalCreateSessionCompleteHandle);

        // Broadcast custom delegate, parameter: not successful
        OnCreateSessionComplete.Broadcast(false);
    }
}

void UMultiplayerSubsystem::FindSessions(int32 MaxSearchResults)
{
    if (!SessionInterface.IsValid())
    {
        return;
    }

    InternalFindSessionsCompleteHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(InternalFindSessionsComplete);

    LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
    LastSessionSearch->MaxSearchResults = MaxSearchResults;
    LastSessionSearch->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
    LastSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

    const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
    if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
    {
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(InternalFindSessionsCompleteHandle);

        OnFindSessionsComplete.Broadcast({}, false);
    }
}

void UMultiplayerSubsystem::JoinSession(const FOnlineSessionSearchResult& SessionResult)
{
    if (!SessionInterface.IsValid())
    {
        OnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
        return;
    }

    InternalJoinSessionCompleteHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(InternalJoinSessionComplete);

    const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
    if (!SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionResult))
    {
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(InternalJoinSessionCompleteHandle);

        OnJoinSessionComplete.Broadcast(EOnJoinSessionCompleteResult::UnknownError);
    }
}

void UMultiplayerSubsystem::StartSession()
{

}

void UMultiplayerSubsystem::DestroySession()
{
    if (!SessionInterface.IsValid())
    {
        OnDestroySessionComplete.Broadcast(false);
        return;
    }

    InternalDestroySessionCompleteHandle = SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(InternalDestroySessionComplete);

    if (!SessionInterface->DestroySession(NAME_GameSession))
    {
        SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(InternalDestroySessionCompleteHandle);
        OnDestroySessionComplete.Broadcast(false);
    }
}

void UMultiplayerSubsystem::CreateSessionCompleteCallback(FName SessionName, bool bWasSuccessful)
{
    if (SessionInterface)
    {
        SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(InternalCreateSessionCompleteHandle);
    }

    OnCreateSessionComplete.Broadcast(bWasSuccessful);
}

void UMultiplayerSubsystem::FindSessionsCompleteCallback(bool bWasSuccessful)
{
    if (SessionInterface)
    {
        SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(InternalFindSessionsCompleteHandle);
    }

    if (LastSessionSearch->SearchResults.Num() <= 0)
    {
        OnFindSessionsComplete.Broadcast({}, false);
        return;
    }

    OnFindSessionsComplete.Broadcast(LastSessionSearch->SearchResults, bWasSuccessful);
}

void UMultiplayerSubsystem::JoinSessionCompleteCallback(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    if (SessionInterface)
    {
        SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(InternalJoinSessionCompleteHandle);
    }

    OnJoinSessionComplete.Broadcast(Result);
}

void UMultiplayerSubsystem::StartSessionCompleteCallback(FName SessionName, bool bWasSuccessful)
{

}

void UMultiplayerSubsystem::DestroySessionCompleteCallback(FName SessionName, bool bWasSuccessful)
{
    if (SessionInterface)
    {
        SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(InternalDestroySessionCompleteHandle);
    }
    if (bWasSuccessful && bCreateSessionOnDestroy)
    {
        // So we won't create another session again accidently
        bCreateSessionOnDestroy = false;
        CreateSession(LastNumPublicConnections, LastMatchType);
    }
    OnDestroySessionComplete.Broadcast(bWasSuccessful);
}

