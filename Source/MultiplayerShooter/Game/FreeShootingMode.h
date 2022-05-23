#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FreeShootingMode.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API AFreeShootingMode : public AGameMode
{
    GENERATED_BODY()
    
public:
    AFreeShootingMode();
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;
};
