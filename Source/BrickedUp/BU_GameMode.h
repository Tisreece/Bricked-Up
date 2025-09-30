// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BU_GameMode.generated.h"

class AAbilityDrop;

//Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreChanged);

UCLASS()
class BRICKEDUP_API ABU_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Scoring") float Score = 0.0f;
	UPROPERTY(BlueprintAssignable, Category="Scoring") FScoreChanged ScoreChanged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring") float CheckpointInterval = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gamestate|Start") bool GameStart = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gamestate|End") bool Victory = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drop") TMap<TSubclassOf<AAbilityDrop>, float> DropList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drop") bool DebugDrop = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drop") TArray<TSubclassOf<AAbilityDrop>> DebugDropList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drop|Chance") float DropChance = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drop|Chance") float PositiveDropChance = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drop|Chance") float NegativeDropChance = 10.0f;

	//Functions
	UFUNCTION(BlueprintCallable, Category="Lose Condition") void CheckBallCount(int32& BallCount);

	UFUNCTION(BlueprintCallable, Category="Scoring") void AddScore(float ScoreToAdd);
	UFUNCTION(BlueprintCallable, Category="Steam|Achievements") void CheckScoreAchievements();

	UFUNCTION(BlueprintCallable, Category="Drop") void GetDrop(TSubclassOf<AAbilityDrop>& Drop, bool& ShouldDrop);
	UFUNCTION(BlueprintCallable, Category="Drop") void GetPositiveDropChance(bool& PositiveDrop);

	//Events
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Lose Condition") void BallDestroyed();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Lose Condition") void BrickHitPlayer();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Lose Condition") void LoseGame();
	UFUNCTION(BlueprintImplementableEVent, BlueprintCallable, Category="Win Condition") void WinGame();
	
};
