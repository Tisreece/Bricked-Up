#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Fire.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInterface_Fire : public UInterface
{
    GENERATED_BODY()
};

class BRICKEDUP_API IInterface_Fire
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability|Paddle Gun") void FirePressed();
};