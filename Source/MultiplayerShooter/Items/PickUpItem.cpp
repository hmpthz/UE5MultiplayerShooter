#include "PickUpItem.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "NiagaraComponent.h"


APickUpItem::APickUpItem()
{
    // Rotate
    PrimaryActorTick.bCanEverTick = true;

    OverlapSphere->AddLocalOffset(FVector(0.f, 0.f, 85.f));
    Mesh->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));

    ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupEffectComponent"));
    ItemEffect->SetupAttachment(RootComponent);
}

void APickUpItem::BeginPlay()
{
    Super::BeginPlay();
    
}

void APickUpItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Mesh)
    {
        Mesh->AddWorldRotation(FRotator(0.f, RotateRate * DeltaTime, 0.f));
    }
}

