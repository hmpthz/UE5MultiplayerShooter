#pragma once
#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "PickUpItem.generated.h"


/*
    A more functional class, including static mesh, pick up items can have particle effect and rotating.
    Note: Right now this isn't pickable inside the sphere of ItemComponent,
    it should only overlap with Pawn object type, which is the capsule of character
*/
UCLASS()
class MULTIPLAYERSHOOTER_API APickUpItem : public APickUpBase
{
    GENERATED_BODY()
    
public:	
    APickUpItem();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    class UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pick Up Properties")
    class UNiagaraComponent* ItemEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

public:
    /* Some getters / setters */

    FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
};
