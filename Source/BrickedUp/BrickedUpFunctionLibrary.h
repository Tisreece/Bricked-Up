#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BrickedUpFunctionLibrary.generated.h"

class ABall;

UCLASS()
class BRICKEDUP_API UBrickedUpFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Audio") static void PlayBallHitAudio(ABall* Ball, USoundBase* HitAudioToPlay);
};