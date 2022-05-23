#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API ALobbyGameMode : public AGameMode
{
    GENERATED_BODY()
    
public:
    virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
    /* Maps path */

    UPROPERTY(EditAnyWhere)
    FString FreeShootingPath;

    UPROPERTY(EditAnyWhere)
    FString TeamShootingPath;

    UPROPERTY(EditAnyWhere)
    FString CaptureTheFlagPath;

    /* Implement a countdown timer in blueprint */
    UFUNCTION(BlueprintImplementableEvent)
    void StartCountdown();

    /* Should be called when countdown to zero */
    UFUNCTION(BlueprintCallable)
    void TravelToDesiredMap();
};
