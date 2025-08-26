#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"
#include "Interface_Fire.h"

#include "AbilityComponentPaddleGun.generated.h"

class APaddleGunBullet;

UCLASS()
class BRICKEDUP_API UAbilityComponentPaddleGun : public UAbilityComponentMaster , public IInterface_Fire
{
	GENERATED_BODY()

public:
    UAbilityComponentPaddleGun();

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Gun") float Ammo;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Gun") float StartingAmmo = 20.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Gun") TSubclassOf<APaddleGunBullet> BulletClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio") USoundBase* FireSound;

    //Functions
    UFUNCTION(BlueprintCallable, Category="Ability") void SetupAbility();
    UFUNCTION(BlueprintCallable, Category="Ability") void RemoveAbility();
    UFUNCTION(BlueprintCallable, Category="Ability") void AddAmmo(float AmountToAdd);
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Ability") bool HasAmmo() const;
    UFUNCTION(BlueprintCallable, Category="Ability") void FireGun();
    UFUNCTION(BlueprintCallable, Category="Ability") void SpawnBullets();
};