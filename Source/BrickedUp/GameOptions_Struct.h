#pragma once

#include "CoreMinimal.h"
#include "GameOptions_Struct.generated.h"

USTRUCT(BlueprintType)
struct FGameOptions_Struct
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Audio",      meta=(ToolTip="0.0 - 1.0", ClampMin="0.0", ClampMax="1.0"))   float MasterVolume = 1.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Graphics",   meta=(ToolTip="0 = 1080p", ClampMin="0", ClampMax="1"))       int32 Resolution = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Graphics",   meta=(ToolTip="0 - 4", ClampMin="0", ClampMax="4"))           int32 GraphicsQuality = 4;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Graphics",   meta=(ToolTip="0 - 4", ClampMin="0", ClampMax="4"))           int32 ShadowQuality = 4;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Graphics",   meta=(ToolTip="0 - 4", ClampMin="0", ClampMax="4"))           int32 TextureQuality = 4;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Graphics",   meta=(ToolTip="30 = 240", ClampMin="30", ClampMax="240"))     int32 FrameRateLimit = 60;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Graphics",   meta=(ToolTip="Enable or Disable VSync"))                     bool VSync = true;
};