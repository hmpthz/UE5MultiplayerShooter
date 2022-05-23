#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSubsystem.generated.h"

/* Delegates declaration, */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_OneParam(FMultiplayerOnJoinSessionComplete, EOnJoinSessionCompleteResult::Type Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnStartSessionComplete, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnDestroySessionComplete, bool, bWasSuccessful);

/*
    Functions, delegates and callbacks for managing online subsytem sessions
*/
UCLASS()
class MULTIPLAYERSYSTEM_API UMultiplayerSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UMultiplayerSubsystem();

    /* Session settings */

    int32 DesiredNumPublicConnections;
    FString DesiredMatchType;

    /* Session API exposed to other classes */

    void CreateSession(int32 NumPublicConnections, FString MatchType);
    void FindSessions(int32 MaxSearchResults);
    void JoinSession(const FOnlineSessionSearchResult& SessionResult);
    void StartSession();
    void DestroySession();
    
    /* Custom delegates exposed to other classes so they can bind custom callbacks */
    
    FMultiplayerOnCreateSessionComplete OnCreateSessionComplete;
    FMultiplayerOnFindSessionsComplete OnFindSessionsComplete;
    FMultiplayerOnJoinSessionComplete OnJoinSessionComplete;
    FMultiplayerOnStartSessionComplete OnStartSessionComplete;
    FMultiplayerOnDestroySessionComplete OnDestroySessionComplete;

protected:
    /* Keep the previous information */

    IOnlineSessionPtr SessionInterface;
    TSharedPtr<FOnlineSessionSettings> LastSessionSettings;
    TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

    bool bCreateSessionOnDestroy;
    int32 LastNumPublicConnections;
    FString LastMatchType;

    /* Internal callbacks for the internal delegates below */
    
    void CreateSessionCompleteCallback(FName SessionName, bool bWasSuccessful);
    void FindSessionsCompleteCallback(bool bWasSuccessful);
    void JoinSessionCompleteCallback(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
    void StartSessionCompleteCallback(FName SessionName, bool bWasSuccessful);
    void DestroySessionCompleteCallback(FName SessionName, bool bWasSuccessful);

    /* Internal delegates, separate logics from custom delegates which will be executed by other classes */
    
    FOnCreateSessionCompleteDelegate InternalCreateSessionComplete;
    FDelegateHandle InternalCreateSessionCompleteHandle;
    FOnFindSessionsCompleteDelegate InternalFindSessionsComplete;
    FDelegateHandle InternalFindSessionsCompleteHandle;
    FOnJoinSessionCompleteDelegate InternalJoinSessionComplete;
    FDelegateHandle InternalJoinSessionCompleteHandle;
    FOnStartSessionCompleteDelegate InternalStartSessionComplete;
    FDelegateHandle InternalStartSessionCompleteHandle;
    FOnDestroySessionCompleteDelegate InternalDestroySessionComplete;
    FDelegateHandle InternalDestroySessionCompleteHandle;
};
