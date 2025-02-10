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

	//Functions
	UFUNCTION(BlueprintCallable, Category="Lose Condition") void CheckBallCount(int32& BallCount);

	//Events
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Lose Condition") void BallDestroyed();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Lose Condition") void BrickHitPlayer();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Lose Condition") void LoseGame();
	
};
