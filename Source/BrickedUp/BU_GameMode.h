// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BU_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class BRICKEDUP_API ABU_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Scoring") float Score = 0.0f;

	//Functions
	UFUNCTION(BlueprintCallable, Category="Lose Condition") void CheckBallCount(int32& BallCount);

	UFUNCTION(BlueprintCallable, Category="Scoring") void AddScore(float ScoreToAdd);

	//Events
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Lose Condition") void BallDestroyed();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Lose Condition") void BrickHitPlayer();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Lose Condition") void LoseGame();
	
};
