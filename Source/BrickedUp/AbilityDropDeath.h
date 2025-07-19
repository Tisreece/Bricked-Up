#pragma once

#include "CoreMinimal.h"
#include "AbilityDrop.h"

#include "AbilityDropDeath.generated.h"

UCLASS()
class BRICKEDUP_API AAbilityDropDeath : public AAbilityDrop
{
    GENERATED_BODY()

public:
    AAbilityDropDeath();

    UFUNCTION(BlueprintCallable, Category="Ability|Death") void Die();
};