#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../MultiplayerShooter.h"
#include "PickUpBase.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API APickUpBase : public AActor
{
    GENERATED_BODY()
    
public:	
    APickUpBase();

    UFUNCTION(BlueprintCallable)
    void PlayPickUpEffect();

    UFUNCTION(BlueprintImplementableEvent)
    void TestF();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pick Up Properties")
    class USphereComponent* OverlapSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pick Up Properties")
    class UWidgetComponent* PickupWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pick Up Properties")
    class USoundCue* PickupSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pick Up Properties")
    class UNiagaraSystem* PickupEffect;
};
