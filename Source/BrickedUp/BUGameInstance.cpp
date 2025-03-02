// Fill out your copyright notice in the Description page of Project Settings.


#include "BUGameInstance.h"
#include "BUSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "BU_GameMode.h"
#include "Algo/Sort.h"
#include "LeaderboardEntry_Struct.h"

void UBUGameInstance::Init()
{
    Super::Init();
}

void UBUGameInstance::LoadGame()
{
   if(UGameplayStatics::DoesSaveGameExist(GameSlotName, 0)) 
   {
        SaveGameRef = Cast<UBUSaveGame>(UGameplayStatics::LoadGameFromSlot(GameSlotName, 0));

        if (SaveGameRef)
        {
            //Save Game Loaded
        }
   }
   else //Save game slot does not exist
   {
    CreateNewSave();
   }
}

void UBUGameInstance::CreateNewSave()
{
    SaveGameRef = Cast<UBUSaveGame>(UGameplayStatics::CreateSaveGameObject(UBUSaveGame::StaticClass()));

    if (SaveGameRef)
    {
        UGameplayStatics::SaveGameToSlot(SaveGameRef, GameSlotName, 0);
    }
}

void UBUGameInstance::InsertLeaderboardEntry(FString EntryName)
{
    //Get the score from the game mode
    ABU_GameMode* CurrentGM = Cast<ABU_GameMode>(GetWorld()->GetAuthGameMode());
    float NewScore = CurrentGM->Score;

    // Create leaderboard entry
    FLeaderboardEntry_Struct NewEntry;
    NewEntry.Name = EntryName;
    NewEntry.Score = NewScore;

    SaveGameRef->Leaderboard.Add(NewEntry);

    Algo::Sort(SaveGameRef->Leaderboard, [](const FLeaderboardEntry_Struct& A, const FLeaderboardEntry_Struct& B)
    {
        return A.Score > B.Score;
    });

    if (SaveGameRef->Leaderboard.Num() > 10)
    {
        SaveGameRef->Leaderboard.SetNum(10);
    }
}

void UBUGameInstance::CanHighScore(bool& CanHighScore) const
{
    CanHighScore = false;
    
    ABU_GameMode* CurrentGM = Cast<ABU_GameMode>(GetWorld()->GetAuthGameMode());
    float NewScore = CurrentGM->Score;

    if (SaveGameRef->Leaderboard.Num() < 10)
    {
        CanHighScore = true;
        return;
    }
    else
    {
        const FLeaderboardEntry_Struct& TenthEntry = SaveGameRef->Leaderboard[9];

        CanHighScore = NewScore > TenthEntry.Score;
    }
}


