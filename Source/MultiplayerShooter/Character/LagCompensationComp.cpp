#include "LagCompensationComp.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../MultiplayerShooter.h"
#include "DrawDebugHelpers.h"

#include "ShooterCharacter.h"
#include "../Weapons/Weapon.h"


ULagCompensationComp::ULagCompensationComp()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

}

void ULagCompensationComp::BeginPlay()
{
    Super::BeginPlay();
    
}

void ULagCompensationComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}