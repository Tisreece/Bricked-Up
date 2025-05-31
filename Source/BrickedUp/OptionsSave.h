#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameOptions_Struct.h"

#include "OptionsSave.generated.h"

UCLASS()
class BRICKEDUP_API UOptionsSave : public USaveGame
{
    GENERATED_BODY()

public:
    UOptionsSave();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Options") FGameOptions_Struct GameOptions;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Game Options") TArray<int32> FrameRateOptions;
};
