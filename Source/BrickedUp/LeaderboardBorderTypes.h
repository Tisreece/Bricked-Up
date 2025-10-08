#pragma once

#include "CoreMinimal.h"
#include "LeaderboardBorderTypes.generated.h"

UENUM(BlueprintType) 
enum class ELeaderboardBorderTypes : uint8
{
    Default     UMETA(DisplayName = "Default"),
    Bronze      UMETA(DIsplayName = "Bronze"),
    Silver      UMETA(DisplayName = "Silver"),
    Gold        UMETA(DisplayName = "Gold")
};