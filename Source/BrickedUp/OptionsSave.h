#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameOptions_Struct.h"

#include "OptionsSave.generated.h"

UCLASS()
class BRICKEDUP_API UOptionsSave : public USsaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Game Options") FGameOptions_Struct GameOptions;
};
