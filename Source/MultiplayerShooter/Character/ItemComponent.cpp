#include "ItemComponent.h"
#include "TimerManager.h"
#include "ShooterCharacter.h"
#include "../Weapons/Weapon.h"


UItemComponent::UItemComponent()
{
    SetCollisionObjectType(ECC_PickUp);
    SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    SetCollisionResponseToChannel(ECC_PickUp, ECollisionResponse::ECR_Overlap);
}

void UItemComponent::BeginPlay()
{
    Super::BeginPlay();
    
    // Only locally controlled character can detect overlapped items
    APawn* Pawn = Cast<APawn>(GetOwner());
    if (Pawn && Pawn->IsLocallyControlled())
    {
        OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
        OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereEndOverlap);
    }
}

void UItemComponent::UpdateNearestWeapon()
{
    AWeapon* NewNearestWeapon = nullptr;
    float MinDistance = TNumericLimits<float>::Max();
    for (AWeapon* Weapon : OverlappedWeapons)
    {
        float D = GetOwner()->GetDistanceTo(Weapon);
        if (D < MinDistance)
        {
            MinDistance = D;
            NewNearestWeapon = Weapon;
        }
    }

    SwapVisibleWidget(NewNearestWeapon);
}

void UItemComponent::SwapVisibleWidget(AWeapon* NewNearestWeapon)
{
    if (NearestWeapon)
    {
        NearestWeapon->ShowPickUpWidget(false);
    }
    if (NewNearestWeapon)
    {
        NewNearestWeapon->ShowPickUpWidget(true);
    }
    NearestWeapon = NewNearestWeapon;
}

void UItemComponent::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AWeapon* Weapon = Cast<AWeapon>(OtherActor);
    if (!Weapon) return;

    OverlappedWeapons.Add(Weapon);
    if (OverlappedWeapons.Num() == 1)
    {
        // The first detected item, immediately update widget
        SwapVisibleWidget(Weapon);
    }
    else
    {
        // More than one items in the area, update nearest item occasionally
        auto& TimerManager = GetWorld()->GetTimerManager();
        if (TimerManager.IsTimerActive(UpdateTimer))
        {
            // Update timer is running, don't do anything
            return;
        }
        // start timer
        TimerManager.SetTimer(
            UpdateTimer,
            this, &ThisClass::UpdateNearestWeapon,
            UpdateNearestRate, true,
            UpdateNearestRate
        );
    }
}

void UItemComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AWeapon* Weapon = Cast<AWeapon>(OtherActor);
    if (!Weapon) return;

    OverlappedWeapons.Remove(Weapon);
    // immediately hide the old widget
    if (Weapon == NearestWeapon)
    {
        SwapVisibleWidget(nullptr);
    }
    // now only one left, no need to update
    if (OverlappedWeapons.Num() == 1)
    {
        GetWorld()->GetTimerManager().ClearTimer(UpdateTimer);
    }
}
