#include "PickUpBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "NiagaraFunctionLibrary.h"


APickUpBase::APickUpBase()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;

    SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));

    OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
    OverlapSphere->SetupAttachment(RootComponent);
    OverlapSphere->SetSphereRadius(60);
    
    OverlapSphere->SetCollisionObjectType(ECC_PickUp);
    OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    OverlapSphere->SetCollisionResponseToChannel(ECC_PickUp, ECollisionResponse::ECR_Overlap);

    PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
    PickupWidget->SetupAttachment(RootComponent);
    // Default doesn't show anything
    ShowPickUpWidget(false);
}

void APickUpBase::ShowPickUpWidget(bool bShow)
{
    if (PickupWidget)
    {
        PickupWidget->SetVisibility(bShow);
    }
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
