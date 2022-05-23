#include "BuffComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShooterCharacter.h"


UBuffComponent::UBuffComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

}

void UBuffComponent::BeginPlay()
{
    Super::BeginPlay();
    
}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}