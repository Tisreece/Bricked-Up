// Fill out your copyright notice in the Description page of Project Settings.


#include "BU_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Ball.h"
#include "AbilityDrop.h"

void ABU_GameMode::CheckBallCount(int32& BallCount)
{
    TArray<AActor*> FoundBalls;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), FoundBalls);

    BallCount = FoundBalls.Num();
}

void ABU_GameMode::AddScore(float ScoreToAdd)
{
    this->Score += ScoreToAdd;
    ScoreChanged.Broadcast();
}

void ABU_GameMode::GetDrop(TSubclassOf<AAbilityDrop>& Drop, bool& ShouldDrop)
{
    //Calculate Drop Chance
    float RandomValue = FMath::RandRange(0.0f, 100.0f);
    ShouldDrop = (RandomValue <= DropChance);

    if (ShouldDrop)
    {
        if (!DebugDrop)
        {
            float TotalWeight = 0.0f;
            for (const auto& Elem : DropList)
            {
                TotalWeight += Elem.Value;
            }

            float RandomWeight = FMath::RandRange(0.0f, TotalWeight);
            float Cumulative = 0.0f;

            for (const auto& Elem : DropList)
            {
                Cumulative += Elem.Value;
                if (RandomWeight <= Cumulative)
                {
                    Drop = Elem.Key;
                    break;
                }
            }
        }
        else
        {
            int32 RandomIndex = FMath::RandRange(0, DebugDropList.Num() - 1);
            Drop = DebugDropList[RandomIndex];
        }
    }
}

void ABU_GameMode::GetPositiveDropChance(bool& PositiveDrop)
{
    float TotalWeight = 0.0f;
    TotalWeight = PositiveDropChance + NegativeDropChance;

    float RandomValue = FMath::RandRange(0.0f, TotalWeight);
    PositiveDrop = (RandomValue <= PositiveDropChance);
}
