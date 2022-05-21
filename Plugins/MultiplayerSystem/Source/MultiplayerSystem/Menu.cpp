#include "Menu.h"
#include "Components/Button.h"
#include "MultiplayerSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"


void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString Path)
{
    LobbyPath = FString::Printf(TEXT("%s?listen"), *Path);
    NumPublicConnections = NumberOfPublicConnections;
    MatchType = TypeOfMatch;
    AddToViewport();
    SetVisibility(ESlateVisibility::Visible);
    bIsFocusable = true;

    UWorld* World = GetWorld();
    if (World)
    {
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if (PlayerController)
        {
            // let player conrol the Menu UI
            FInputModeUIOnly InputModeData;
            // focus input on UI
            InputModeData.SetWidgetToFocus(TakeWidget());
            InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            PlayerController->SetInputMode(InputModeData);
            PlayerController->SetShowMouseCursor(true);
        }
    }

    UGameInstance* GameInstance = GetGameInstance();
    if (GameInstance)
    {
        MultiplayerSubsystem = GameInstance->GetSubsystem<UMultiplayerSubsystem>();
    }

    if (MultiplayerSubsystem)
    {
        MultiplayerSubsystem->OnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
        MultiplayerSubsystem->OnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
        MultiplayerSubsystem->OnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
        MultiplayerSubsystem->OnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
        MultiplayerSubsystem->OnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
    }
}

bool UMenu::Initialize()
{
    if (!Super::Initialize())
    {
        return false;
    }

    if (HostButton)
    {
        HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
    }
    if (JoinButton)
    {
        JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
    }

    return true;
}

void UMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    MenuTearDown();
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}

void UMenu::MenuTearDown()
{
    RemoveFromParent();
    UWorld* World = GetWorld();
    if (World)
    {
        APlayerController* PlayerController = World->GetFirstPlayerController();
        if (PlayerController)
        {
            FInputModeGameOnly InputModeData;
            PlayerController->SetInputMode(InputModeData);
            PlayerController->SetShowMouseCursor(false);
        }
    }
}

void UMenu::HostButtonClicked()
{
    HostButton->SetIsEnabled(false);
    if (MultiplayerSubsystem)
    {
        MultiplayerSubsystem->CreateSession(NumPublicConnections, MatchType);
    }
}

void UMenu::JoinButtonClicked()
{
    JoinButton->SetIsEnabled(false);
    if (MultiplayerSubsystem)
    {
        MultiplayerSubsystem->FindSessions(10000);
    }
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue,
                    FString(TEXT("Create session successfully!")));
            }
            World->ServerTravel(LobbyPath);
        }
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
                FString(TEXT("Failed to create session!")));
        }
        HostButton->SetIsEnabled(true);
    }
}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
    if (!MultiplayerSubsystem)
    {
        return;
    }

    for (auto Result : SessionResults)
    {
        FString SessionValue;
        Result.Session.SessionSettings.Get(FName("MatchType"), SessionValue);
        if (SessionValue == MatchType)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue,
                    FString(TEXT("Find session successfully!")));
            }
            MultiplayerSubsystem->JoinSession(Result);
            return;
        }
    }
    if (!bWasSuccessful || SessionResults.Num() == 0)
    {
        JoinButton->SetIsEnabled(true);
    }
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
            FString(TEXT("Failed to find session!")));
    }
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            FString Address;
            SessionInterface->GetResolvedConnectString(NAME_GameSession, Address);

            APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
            if (PlayerController)
            {
                PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
            }
        }
    }

    // Can happen if host exits the game but doesn't destroy the session
    if (Result != EOnJoinSessionCompleteResult::Success)
    {
        JoinButton->SetIsEnabled(true);
    }
}

void UMenu::OnStartSession(bool bWasSuccessful)
{

}

void UMenu::OnDestroySession(bool bWasSuccessful)
{

}
