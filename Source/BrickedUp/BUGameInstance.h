// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "steam/steam_api.h"
#include "steam/isteaminventory.h"

#include "BUGameInstance.generated.h"

class UBUSaveGame;
class UOptionsSave;

UCLASS()
class BRICKEDUP_API UBUGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

public:
	UBUGameInstance();
	~UBUGameInstance();

	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SaveGame") UBUSaveGame* SaveGameRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SaveGame") FString GameSlotName = "Slot 1";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SaveGame") UOptionsSave* OptionsSaveRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SaveGame") FString OptionsSlotName = "Options";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio") USoundMix* SoundMix;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio") USoundClass* SoundClass;

	//Functions	
	UFUNCTION(BlueprintCallable, Category="SaveGame") void LoadGame();
	UFUNCTION(BlueprintCallable, Category="SaveGame") void CreateNewSave();
	UFUNCTION(BlueprintCallable, Category="SaveGame") void SetGameOptions(bool SetAudioOptions, bool SetGraphicsOptions);
	UFUNCTION(BlueprintCallable, category="Leaderboard") void InsertLeaderboardEntry(FString EntryName);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Leaderboard") void CanHighScore(bool& CanHighScore) const;

	//Events
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="SaveGame") void SaveGame();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Leaderboard") void AddNewScore(const FString& EntryName);

	// Steam Functions and Variables
public:
	
	//Variables
	SteamInventoryResult_t PendingResultHandle = k_SteamInventoryResultInvalid;
	SteamInventoryResult_t ConsumeResultHandle = k_SteamInventoryResultInvalid;
	bool bPendingRemove = false;
	int32 PendingRemoveItemID = 0;
	int32 PendingRemoveQuantity = 0;
	bool bPendingUniqueAdd = false;
	int32 PendingUniqueAddItemID = 0;
	int32 PendingUniqueAddQuantity = 0;
	TMap<SteamItemInstanceID_t, int32> RecentlyConsumedItems;
	TArray<int32> RecentlyAddedItemTypes;


	//Functions
	void OnInventoryResultReady(SteamInventoryResultReady_t* Callback);
	void OnConsumeResultReady(SteamInventoryResultReady_t* Callback);
	void AddRecentlyConsumedItem(SteamItemInstanceID_t InstanceID, int32 ItemID);
	void RemoveRecentlyConsumedItem(SteamItemInstanceID_t InstanceID);
	void AddRecentlyAddedItemType(int32 ItemID);
	void RemoveRecentlyAddedItemType(int32 ItemID);

private:
	CCallback<UBUGameInstance, SteamInventoryResultReady_t, false>* InventoryResultCallback;
	CCallback<UBUGameInstance, SteamInventoryResultReady_t, false>* ConsumeResultCallback;
};
