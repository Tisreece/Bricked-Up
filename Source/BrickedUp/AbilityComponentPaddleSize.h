#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"

#include "AbilityComponentPaddleSize.generated.h"

UCLASS()
class BRICKEDUP_API UAbilityComponentPaddleSize : public UAbilityComponentMaster
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Stats") TMap<int32, FVector> PaddleSizeLevels;

    UFUNCTION(BlueprintCallable, Category = "Ability") void SetPaddleSize(int32 NewLevel);
};