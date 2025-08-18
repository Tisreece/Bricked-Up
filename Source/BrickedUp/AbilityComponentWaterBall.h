#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"

#include "AbilityComponentWaterBall.generated.h"

UCLASS()
class BRICKEDUP_API UAbilityComponentWaterBall : public UAbilityComponentMaster
{
    GENERATED_BODY()
public:
    UAbilityComponentWaterBall();

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh") UMaterial* BallMaterial;

    //Functions
    UFUNCTION(BlueprintCallable, Category="Ability|Water Ball") void SetBallMaterial();
};
