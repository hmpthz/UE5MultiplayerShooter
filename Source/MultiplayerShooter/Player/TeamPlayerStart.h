#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "../MetaTypes/Team.h"
#include "TeamPlayerStart.generated.h"


UCLASS()
class MULTIPLAYERSHOOTER_API ATeamPlayerStart : public APlayerStart
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    ETeam Team;
};
