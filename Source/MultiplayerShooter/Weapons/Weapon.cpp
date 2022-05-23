#include "Weapon.h"
#include "../Character/ShooterCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "Animation/AnimationAsset.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetMathLibrary.h"


AWeapon::AWeapon()
{
    // Don't need to tick every frame
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    Mesh->MarkRenderStateDirty();
    Mesh->SetRenderCustomDepth(true);
    Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_PURPLE);
}

void AWeapon::BeginPlay()
{
    Super::BeginPlay();
    
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AWeapon::EnableCustomDepth(bool bEnable)
{
    if (Mesh)
    {
        Mesh->SetRenderCustomDepth(bEnable);
    }
}
