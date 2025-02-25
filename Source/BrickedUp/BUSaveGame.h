// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BUSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BRICKEDUP_API UBUSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	//UBUSaveGame();

	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Leaderboard") TMap<FString, float> Leaderboard;
};
