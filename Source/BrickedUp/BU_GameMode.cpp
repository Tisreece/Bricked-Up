// Fill out your copyright notice in the Description page of Project Settings.


#include "BU_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Ball.h"

void ABU_GameMode::CheckBallCount(int32& BallCount)
{
    TArray<AActor*> FoundBalls;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), FoundBalls);

    BallCount = FoundBalls.Num();
}

void ABU_GameMode::AddScore(float ScoreToAdd)
{
    this->Score += ScoreToAdd;
}

