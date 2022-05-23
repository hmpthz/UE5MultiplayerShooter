#include "ShooterGameState.h"
#include "Net/UnrealNetwork.h"
#include "../Player/ShooterPlayerState.h"
#include "../Player/ShooterPlayerController.h"


void AShooterGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
}