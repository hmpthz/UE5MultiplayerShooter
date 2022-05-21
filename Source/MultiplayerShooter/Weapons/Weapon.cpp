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

    OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    Mesh->MarkRenderStateDirty();
}

void AWeapon::BeginPlay()
{
    Super::BeginPlay();
    
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
