#include "FreeShootingMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

#include "ShooterGameState.h"
#include "../Player/ShooterPlayerController.h"
#include "../Player/ShooterPlayerState.h"


AFreeShootingMode::AFreeShootingMode()
{

}

void AFreeShootingMode::BeginPlay()
{
    Super::BeginPlay();
}

void AFreeShootingMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}