#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_HitBrick.generated.h"

class ABrickMaster;

UINTERFACE(MinimalAPI, Blueprintable)
class UInterface_HitBrick : public UInterface
{
	GENERATED_BODY()
};

class BRICKEDUP_API IInterface_HitBrick
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Hit") void HitBrick(ABrickMaster* HitBrick);
};
