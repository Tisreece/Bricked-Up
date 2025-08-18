#pragma once

#include "CoreMinimal.h"
#include "AbilityComponentMaster.h"
#include "Interface_HitBrick.h"
#include "NiagaraComponent.h"

#include "AbilityComponentExplosiveBall.generated.h"

class ABrickMaster;

UCLASS()
class BRICKEDUP_API UAbilityComponentExplosiveBall : public UAbilityComponentMaster, public IInterface_HitBrick
{
    GENERATED_BODY()
public:
    UAbilityComponentExplosiveBall();

    // Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh") UMaterial* BallMaterial;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hit") ABrickMaster* BrickToExplode;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="VFX") UNiagaraComponent* BallEffect;

    // Functions
    UFUNCTION(BlueprintCallable, Category="Ability|Explosive Ball") void SetBallMaterial();
    UFUNCTION(BlueprintCallable, Category="Ability|Explosive Ball") void ResetBallMaterial(UMaterial* ResetMaterial);
    UFUNCTION(BlueprintCallable, Category="Ability|Explosive Ball") void Explode(TArray<ABrickMaster*> BricksToExplode);
};