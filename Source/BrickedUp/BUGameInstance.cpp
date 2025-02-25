// Fill out your copyright notice in the Description page of Project Settings.


#include "BUGameInstance.h"
#include "BUSaveGame.h"
#include "Kismet/GameplayStatics.h"

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
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Save Game Loaded"));
        }
   }
   else //Save game slot does not exist
   {
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Save Game Does Not Exist"));
    CreateNewSave();
   }
}

void UBUGameInstance::CreateNewSave()
{
    SaveGameRef = Cast<UBUSaveGame>(UGameplayStatics::CreateSaveGameObject(UBUSaveGame::StaticClass()));

    if (SaveGameRef)
    {
        UGameplayStatics::SaveGameToSlot(SaveGameRef, GameSlotName, 0);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Save Game Created"));
    }
}


