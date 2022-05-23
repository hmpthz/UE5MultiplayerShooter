#include "PickUpItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"


APickUpItem::APickUpItem()
{
    // Rotate
    PrimaryActorTick.bCanEverTick = true;

    // only response to character capsule, instead of ItemComponent sphere.
    OverlapSphere->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
    OverlapSphere->SetCollisionResponseToChannel(ECC_PickUp, ECollisionResponse::ECR_Ignore);
    OverlapSphere->AddLocalOffset(FVector(0.f, 0.f, 85.f));

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Mesh->SetRenderCustomDepth(true);
    Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_PURPLE);
    Mesh->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));

    ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupEffectComponent"));
    ItemEffect->SetupAttachment(RootComponent);
}

void APickUpItem::BeginPlay()
{
    Super::BeginPlay();
    
    // Only server can execute overlap event
    if (HasAuthority())
    {
        
    }
}

void APickUpItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Mesh)
    {
        Mesh->AddWorldRotation(FRotator(0.f, RotateRate * DeltaTime, 0.f));
    }
}

