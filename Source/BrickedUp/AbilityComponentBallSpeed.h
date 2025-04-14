#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"

#include "AbilityComponentBallSpeed.generated.h"

UCLASS()
class BRICKEDUP_API UAbilityComponentBallSpeed : public UAbilityComponentMaster
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Stats") TMap<int32, float> BallSpeedLevels; 

    UFUNCTION(BlueprintCallable, Category = "Ability") void SetBallSpeed(int32 NewLevel);
};