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

protected:
    virtual void BeginPlay() override;

        
};
