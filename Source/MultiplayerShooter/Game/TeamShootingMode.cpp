#include "TeamShootingMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGameState.h"
#include "../Player/ShooterPlayerController.h"
#include "../Player/ShooterPlayerState.h"


ATeamShootingMode::ATeamShootingMode()
{

}

void ATeamShootingMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    
}

void ATeamShootingMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);

}