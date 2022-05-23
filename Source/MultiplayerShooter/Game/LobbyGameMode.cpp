#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "MultiplayerSystem/MultiplayerSubsystem.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    int32 NumberPlayers = GameState.Get()->PlayerArray.Num();

    UGameInstance* GameInstance = GetGameInstance();
    if (!GameInstance) return;

    UMultiplayerSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSubsystem>();
    if (!Subsystem) return;

    if (NumberPlayers == Subsystem->DesiredNumPublicConnections)
    {
        StartCountdown();
    }
}

void ALobbyGameMode::TravelToDesiredMap()
{
    UGameInstance* GameInstance = GetGameInstance();
    if (!GameInstance) return;

    UMultiplayerSubsystem* Subsystem = GameInstance->GetSubsystem<UMultiplayerSubsystem>();
    if (!Subsystem) return;

    bUseSeamlessTravel = true;
    UWorld* World = GetWorld();
    if (World)
    {
        FString MatchType = Subsystem->DesiredMatchType;
        if (MatchType == "FreeShooting")
        {
            World->ServerTravel(FString::Printf(TEXT("%s?listen"), *FreeShootingPath));
        }
        else if (MatchType == "TeamShooting")
        {
        	World->ServerTravel(FString::Printf(TEXT("%s?listen"), *TeamShootingPath));
        }
        else if (MatchType == "CaptureTheFlag")
        {
        	World->ServerTravel(FString::Printf(TEXT("%s?listen"), *CaptureTheFlagPath));
        }
    }
}