#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"
#include "Interface_Fire.h"

#include "AbilityComponentPaddleGun.generated.h"

UCLASS()
class BRICKEDUP_API UAbilityComponentPaddleGun : public UAbilityComponentMaster , public IInterface_Fire
{
	GENERATED_BODY()

public:
    UAbilityComponentPaddleGun();

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Gun") float Ammo;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Gun") float StartingAmmo = 50.0f;

    //Functions
    UFUNCTION(BlueprintCallable, Category="Ability") void SetupAbility();
    UFUNCTION(BlueprintCallable, Category="Ability") void RemoveAbility();
    UFUNCTION(BlueprintCallable, Category="Ability") void AddAmmo(float AmountToAdd);
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ability") bool HasAmmo() const;
    UFUNCTION(BlueprintCallable, Category="Ability") void FireGun();
};