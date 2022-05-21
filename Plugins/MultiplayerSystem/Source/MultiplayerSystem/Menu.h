#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Menu.generated.h"


UCLASS()
class MULTIPLAYERSYSTEM_API UMenu : public UUserWidget
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable)
    void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("FreeShooting")), FString LobbyPath = FString(TEXT("/Game/Maps/Lobby")));

protected:
    virtual bool Initialize() override;
    virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
    void MenuTearDown();

    /* Subsystem pointer */
    class UMultiplayerSubsystem* MultiplayerSubsystem;

    /* Buttons and click callbacks */

    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    class UButton* HostButton;
    UPROPERTY(VisibleAnywhere, meta = (BindWidget))
    UButton* JoinButton;

    UFUNCTION()
    void HostButtonClicked();
    UFUNCTION()
    void JoinButtonClicked();

    /* Callbacks for the custom delegates from MultiplayerSubsystem */
    
    UFUNCTION()
    void OnCreateSession(bool bWasSuccessful);
    void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
    void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
    UFUNCTION()
    void OnStartSession(bool bWasSuccessful);
    UFUNCTION()
    void OnDestroySession(bool bWasSuccessful);

    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int32 NumPublicConnections;

    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FString MatchType;

    FString LobbyPath;
};
