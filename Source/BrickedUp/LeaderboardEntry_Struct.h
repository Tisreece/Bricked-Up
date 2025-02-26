#pragma once

#include "CoreMinimal.h"
#include "LeaderboardEntry_Struct.generated.h"

USTRUCT(BlueprintType)
struct FLeaderboardEntry_Struct
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Leaderboard") FString Name;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Leaderboard") float Score;

};