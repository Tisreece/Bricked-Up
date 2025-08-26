#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_HitCeiling.generated.h"

UINTERFACE(MinimalAPI)
class UInterface_HitCeiling : public UInterface
{
    GENERATED_BODY()
};

class BRICKEDUP_API IInterface_HitCeiling
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="HitCeiling") void HitCeiling();
};