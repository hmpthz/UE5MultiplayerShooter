#pragma once
#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "PickUpItem.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API APickUpItem : public APickUpBase
{
    GENERATED_BODY()
    
public:	
    APickUpItem();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    class UNiagaraComponent* ItemEffect;

    UPROPERTY(EditAnywhere)
    float RotateRate = 45.f;

    UFUNCTION(BlueprintImplementableEvent)
    void OnSphereOverlap(
    	UPrimitiveComponent* OverlappedComponent,
    	AActor* OtherActor,
    	UPrimitiveComponent* OtherComp,
    	int32 OtherBodyIndex,
    	bool bFromSweep,
    	const FHitResult& SweepResult
    );
};
