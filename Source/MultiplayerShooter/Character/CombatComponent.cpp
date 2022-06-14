#include "CombatComponent.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "ShooterCharacter.h"
#include "ShooterCharacterAnim.h"
#include "../Weapons/Weapon.h"


UCombatComponent::UCombatComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

}

void UCombatComponent::BeginPlay()
{
    Super::BeginPlay();
    
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void UCombatComponent::EquipWeapon(AWeapon* ToEquip)
{
    if (!Character || !ToEquip) return;
    if (CombatState != ECombatState::ECS_Unoccupied) return;

    if (ToEquip->GetWeaponType() == EWeaponType::EWT_Flag)
    {

    }
    else
    {
        EquipPrimaryWeapon(ToEquip);

        Character->GetCharacterMovement()->bOrientRotationToMovement = false;
        Character->bUseControllerRotationYaw = true;
    }
}

void UCombatComponent::EquipPrimaryWeapon(AWeapon* ToEquip)
{
    EquippedWeapon = ToEquip;
    EquippedWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
    EquippedWeapon->SetOwner(Character);
    EquippedWeapon->PlayPickUpEffect();
}

void UCombatComponent::EquipSecondaryWeapon(AWeapon* ToEquip)
{
}

void UCombatComponent::OnRep_CombatState()
{
}

void UCombatComponent::OnRep_EquippedWeapon()
{
}

void UCombatComponent::OnRep_SecondaryWeapon()
{
}

void UCombatComponent::AttachActorToSocket(AActor* ToAttach, FName SocketName)
{
}
