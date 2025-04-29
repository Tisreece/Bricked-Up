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
            int32 RandomIndex = FMath::RandRange(0, DropList.Num() - 1);
            Drop = DropList[RandomIndex];
        }
        else
        {
            int32 RandomIndex = FMath::RandRange(0, DebugDropList.Num() - 1);
            Drop = DebugDropList[RandomIndex];
        }
    }
}

