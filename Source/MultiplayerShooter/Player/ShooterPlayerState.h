#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "../MetaTypes/Team.h"
#include "ShooterPlayerState.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API AShooterPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};