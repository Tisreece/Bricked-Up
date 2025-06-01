#include "OptionsSave.h"

UOptionsSave::UOptionsSave()
{
    FrameRateOptions = {240, 165, 144, 120, 75, 60, 30};
    GraphicsQualityOptions = {4, 3, 2, 1, 0};
    ResolutionOptions = {
        FIntPoint(2560, 1440),
        FIntPoint(1920, 1080),
        FIntPoint(1600, 900),
        FIntPoint(1366, 768),
        FIntPoint(1280, 720)
    };
}