#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LagCompensationComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERSHOOTER_API ULagCompensationComp : public UActorComponent
{
    GENERATED_BODY()

public:	
    ULagCompensationComp();
    friend class AShooterCharacter;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    virtual void BeginPlay() override;

        
};
