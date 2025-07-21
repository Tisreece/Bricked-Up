#pragma once

#include "CoreMinimal.h"
#include "AbilityDrop.h"

#include "AbilityDropLuck.generated.h"

class AAbilityDrop;

UCLASS()
class BRICKEDUP_API AAbilityDropLuck : public AAbilityDrop
{
    GENERATED_BODY()

public:
    AAbilityDropLuck();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Luck") TMap<TSubclassOf<AAbilityDrop>, float> PositiveAbilityList;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Luck") TMap<TSubclassOf<AAbilityDrop>, float> NegativeAbilityList;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Luck") float PositiveDropIncrease = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Luck") float NegativeDropIncrease = 0.0f;

    UFUNCTION(BlueprintCallable, Category="Ability|Luck") void AddLuckStats(TMap<TSubclassOf<AAbilityDrop>, float> AbilityList, float PositiveDropChance, float NegativeDropChance);
};