#pragma once
#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ItemComponent.generated.h"


/*
    A sphere with a sphere with "PickUp" collision object type,
    detect the overlapped items, and occasionally get the nearest item.
    No replication, only used in locally controlled character.
    (Currently only used for detecting weapons, can be extended further)
*/
UCLASS()
class MULTIPLAYERSHOOTER_API UItemComponent : public USphereComponent
{
    GENERATED_BODY()
    
public:
    UItemComponent();
    friend class AShooterCharacter;

protected:
    virtual void BeginPlay() override;

    /* Nearest weapon to the character inside the array */
    UPROPERTY(BlueprintReadOnly)
    class AWeapon* NearestWeapon;

    UPROPERTY(BlueprintReadOnly)
    TArray<AWeapon*> OverlappedWeapons;

    /* Occasionally update the nearest weapon in array, and set the widget visibility */
    void UpdateNearestWeapon();
    FTimerHandle UpdateTimer;

    /* The time interval for updating nearest item */
    UPROPERTY(EditAnyWhere, meta = (ClampMin = 0))
    float UpdateNearestRate;

    /* Change the current nearest weapon and swap pickup widget visibility */
    void SwapVisibleWidget(AWeapon* NewNearestWeapon);

    /* Add item into array */
    UFUNCTION()
    void OnSphereOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    /* Remove item from array */
    UFUNCTION()
    void OnSphereEndOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex
    );

public:
    /* Some getters / setters */

    FORCEINLINE AWeapon* GetNearestWeapon() const { return NearestWeapon; }
    FORCEINLINE void RemoveWeapon(AWeapon* ToRemove) { OverlappedWeapons.Remove(ToRemove); }
};
