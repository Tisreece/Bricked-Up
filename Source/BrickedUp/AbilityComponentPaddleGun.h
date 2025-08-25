#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"

#include "AbilityComponentPaddleGun.generated.h"

UCLASS()
class BRICKEDUP_API UAbilityComponentPaddleGun : public UAbilityComponentMaster
{
	GENERATED_BODY()

public:
    UAbilityComponentPaddleGun();

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Gun") float Ammo;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Gun") float StartingAmmo = 50.0f;

    //Functions
    UFUNCTION(BlueprintCallable, Category="Ability") void SetupAbility();
};