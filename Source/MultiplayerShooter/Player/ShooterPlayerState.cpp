#include "ShooterPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "../Character/ShooterCharacter.h"
#include "ShooterPlayerController.h"


void AShooterPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}