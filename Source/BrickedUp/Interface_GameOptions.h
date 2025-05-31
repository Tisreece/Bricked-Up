#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_GameOptions.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInterface_GameOptions : public UInterface
{
    GENERATED_BODY()
};

class BRICKEDUP_API IInterface_GameOptions
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Game Options") void GameOptionsClosed();
};