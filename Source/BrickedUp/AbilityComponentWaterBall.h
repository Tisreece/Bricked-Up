#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"
#include "Interface_KillZone.h"

#include "AbilityComponentWaterBall.generated.h"

UCLASS()
class BRICKEDUP_API UAbilityComponentWaterBall : public UAbilityComponentMaster, public IInterface_KillZone
{
    GENERATED_BODY()
public:
    UAbilityComponentWaterBall();

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh") UMaterial* BallMaterial;

    //Functions
    UFUNCTION(BlueprintCallable, Category="Ability|Water Ball") void SetBallMaterial();
    UFUNCTION(BlueprintCallable, Category="Ability|Water Ball") void ResetBallMaterial(UMaterial* ResetMaterial);
    UFUNCTION(BlueprintCallable, Category="Ability|Water Ball") void SetIgnorePlayer();
    UFUNCTION(BlueprintCallable, Category="Steam|Achievements") void TriggerGuardianAngelCheck();
};
