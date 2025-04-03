#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"

#include "AbilityComponentBallSplit.generated.h"

UCLASS()
class BRICKEDUP_API UAbilityComponentBallSplit : public UAbilityComponentMaster
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Ability") void SplitBall();
};