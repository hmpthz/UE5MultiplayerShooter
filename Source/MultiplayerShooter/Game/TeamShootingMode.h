#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TeamShootingMode.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API ATeamShootingMode : public AGameMode
{
    GENERATED_BODY()
    
public:
    ATeamShootingMode();
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;
    
};
