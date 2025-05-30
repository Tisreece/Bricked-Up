#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"

#include "AbilityComponentBallSize.generated.h"

UCLASS()
class BRICKEDUP_API UAbilityComponentBallSize : public UAbilityComponentMaster
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Stats") TMap<int32, FVector> BallSizeLevels; 

    UFUNCTION(BlueprintCallable, Category = "Ability") void SetBallSize(int32 NewLevel);

};