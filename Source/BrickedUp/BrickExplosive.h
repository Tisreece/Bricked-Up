#pragma once

#include "CoreMinimal.h"
#include "BrickMaster.h"

#include "BrickExplosive.generated.h"

UCLASS()
class BRICKEDUP_API ABrickExplosive : public ABrickMaster
{
    GENERATED_BODY()
public:
    ABrickExplosive();

    //Functions
    UFUNCTION(BlueprintCallable, Category="Hit") void Explode(TArray<ABrickMaster*> BricksToExplode);
};