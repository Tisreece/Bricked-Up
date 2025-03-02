// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BUGameInstance.generated.h"

class UBUSaveGame;

UCLASS()
class BRICKEDUP_API UBUGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

public:

	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SaveGame") UBUSaveGame* SaveGameRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SaveGame") FString GameSlotName = "Slot 1";

	//Functions	
	UFUNCTION(BlueprintCallable, Category="SaveGame") void LoadGame();
	UFUNCTION(BlueprintCallable, Category="SaveGame") void CreateNewSave();
	UFUNCTION(BlueprintCallable, category="Leaderboard") void InsertLeaderboardEntry(FString EntryName);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Leaderboard") void CanHighScore(bool& CanHighScore) const;

	//Events
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="SaveGame") void SaveGame();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Leaderboard") void AddNewScore(const FString& EntryName);
		
};
