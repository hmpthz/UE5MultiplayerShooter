#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../MetaTypes/WeaponTypes.h"
#include "../MetaTypes/CombatState.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERSHOOTER_API UCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
    UCombatComponent();
    friend class AShooterCharacter;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    void EquipWeapon(class AWeapon* ToEquip);
    void EquipPrimaryWeapon(AWeapon* ToEquip);
    void EquipSecondaryWeapon(AWeapon* ToEquip);

protected:
    virtual void BeginPlay() override;
    class AShooterCharacter* Character;

    UPROPERTY(ReplicatedUsing = OnRep_CombatState)
    ECombatState CombatState = ECombatState::ECS_Unoccupied;

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EquippedWeapon)
    AWeapon* EquippedWeapon;

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SecondaryWeapon)
    AWeapon* SecondaryWeapon;

    UFUNCTION()
    void OnRep_CombatState();

    UFUNCTION()
    void OnRep_EquippedWeapon();

    UFUNCTION()
    void OnRep_SecondaryWeapon();

    void AttachActorToSocket(AActor* ToAttach, FName SocketName);
};
