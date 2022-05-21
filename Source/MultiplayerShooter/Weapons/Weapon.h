#pragma once
#include "CoreMinimal.h"
#include "../Items/PickUpBase.h"
#include "../MetaTypes/WeaponTypes.h"
#include "../MetaTypes/Team.h"
#include "Weapon.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API AWeapon : public APickUpBase
{
    GENERATED_BODY()
    
public:	
    AWeapon();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnSphereOverlap(
    	UPrimitiveComponent* OverlappedComponent,
    	AActor* OtherActor,
    	UPrimitiveComponent* OtherComp,
    	int32 OtherBodyIndex,
    	bool bFromSweep,
    	const FHitResult& SweepResult
    );

    UFUNCTION()
    void OnSphereEndOverlap(
    	UPrimitiveComponent* OverlappedComponent,
    	AActor* OtherActor,
    	UPrimitiveComponent* OtherComp,
    	int32 OtherBodyIndex
    );
};
