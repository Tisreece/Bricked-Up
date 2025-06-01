// Fill out your copyright notice in the Description page of Project Settings.


#include "BUGameInstance.h"
#include "BUSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "BU_GameMode.h"
#include "Algo/Sort.h"
#include "LeaderboardEntry_Struct.h"
#include "GameOptions_Struct.h"
#include "GameFramework/GameUserSettings.h"
#include "OptionsSave.h"

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

void UBUGameInstance::SetGameOptions(bool SetAudioOptions, bool SetGraphicsOptions)
{
    OptionsSaveRef = Cast<UOptionsSave>(UGameplayStatics::LoadGameFromSlot(OptionsSlotName, 0));

    if (OptionsSaveRef)
    {
        FGameOptions_Struct GameOptions = OptionsSaveRef->GameOptions;

        if (SetAudioOptions)
        {
            UGameplayStatics::SetSoundMixClassOverride(this, SoundMix, SoundClass, GameOptions.MasterVolume, 1.0f, 1.0f);
        }
        if (SetGraphicsOptions)
        {
            UGameUserSettings* Settings = GEngine->GetGameUserSettings();

            //Graphics Settings
            int32 GraphicsQuality = GameOptions.GraphicsQuality;
            Settings->SetViewDistanceQuality(GraphicsQuality);
            Settings->SetAntiAliasingQuality(GraphicsQuality);
            Settings->SetPostProcessingQuality(GraphicsQuality);
            Settings->SetGlobalIlluminationQuality(GraphicsQuality);
            Settings->SetReflectionQuality(GraphicsQuality);
            Settings->SetVisualEffectQuality(GraphicsQuality);
            Settings->SetFoliageQuality(GraphicsQuality);
            Settings->SetShadingQuality(GraphicsQuality);

            //Shadow Setings
            int32 ShadowQuality = GameOptions.ShadowQuality;
            Settings->SetShadowQuality(ShadowQuality);

            //Texture Settings
            int32 TextureQuality = GameOptions.TextureQuality;
            Settings->SetTextureQuality(TextureQuality);

            //Vsync
            Settings->SetVSyncEnabled(GameOptions.VSync);

            //Frame Rate Limit
            Settings->SetFrameRateLimit(GameOptions.FrameRateLimit);

            Settings->ApplySettings(false);
        }
    }
}


