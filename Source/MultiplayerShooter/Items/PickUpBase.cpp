#include "PickUpBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "NiagaraFunctionLibrary.h"


APickUpBase::APickUpBase()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;

    SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

    OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
    OverlapSphere->SetupAttachment(RootComponent);
    OverlapSphere->SetSphereRadius(150.f);
    OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
    Mesh->SetupAttachment(RootComponent);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Mesh->SetRenderCustomDepth(true);
    Mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_PURPLE);

    PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
    PickupWidget->SetupAttachment(RootComponent);
}

void APickUpBase::PlayPickUpEffect()
{
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			PickupSound,
			GetActorLocation()
		);
	}
	if (PickupEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			PickupEffect,
			GetActorLocation(),
			GetActorRotation()
		);
	}
}
