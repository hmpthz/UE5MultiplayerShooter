#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../MultiplayerShooter.h"
#include "PickUpBase.generated.h"


/*
    Base class for pick up items, including overlap sphere, display widget, VFX, SFX, etc.
    Can be used in any objects that can be picked or dropped. (Weapons...)
*/
UCLASS()
class MULTIPLAYERSHOOTER_API APickUpBase : public AActor
{
    GENERATED_BODY()
    
public:	
    APickUpBase();

    UFUNCTION(BlueprintCallable)
    void ShowPickUpWidget(bool bShow);

    UFUNCTION(BlueprintCallable)
    void PlayPickUpEffect();

protected:
    /*
        This is a sphere with "PickUp" collision object type,
        only used for detecting items that can be picked
    */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pick Up Component")
    class USphereComponent* OverlapSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pick Up Component")
    class UWidgetComponent* PickupWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pick Up Assets")
    class USoundCue* PickupSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pick Up Assets")
    class UNiagaraSystem* PickupEffect;

public:
    /* Some getters / setters */

    FORCEINLINE USphereComponent* GetSphere() const { return OverlapSphere; }
    FORCEINLINE UWidgetComponent* GetPickupWidget() const { return PickupWidget; }
};
