#include "BUGameInstance.h"
#include "BrickedUp.h"
#include "BUSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "BU_GameMode.h"
#include "Algo/Sort.h"
#include "LeaderboardEntry_Struct.h"
#include "GameOptions_Struct.h"
#include "GameFramework/GameUserSettings.h"
#include "OptionsSave.h"
#include "GenericPlatform/GenericApplication.h"
#include "Framework/Application/SlateApplication.h"
#include "HAL/PlatformApplicationMisc.h"
#include "SteamFunctionLibrary.h"

UBUGameInstance::UBUGameInstance()
{
    InventoryResultCallback = new CCallback<UBUGameInstance, SteamInventoryResultReady_t, false>(this, &UBUGameInstance::OnInventoryResultReady);
    ConsumeResultCallback = new CCallback<UBUGameInstance, SteamInventoryResultReady_t, false>(this, &UBUGameInstance::OnConsumeResultReady);
}

UBUGameInstance::~UBUGameInstance()
{
    delete InventoryResultCallback;
    delete ConsumeResultCallback;
    InventoryResultCallback = nullptr;
    ConsumeResultCallback = nullptr;
}

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

            //Resolution Settings
            Settings->SetScreenResolution(GameOptions.Resolution);
            
            FDisplayMetrics DisplayMetrics;
            FDisplayMetrics::RebuildDisplayMetrics(DisplayMetrics);
            FIntPoint NativeResolution(DisplayMetrics.PrimaryDisplayWidth, DisplayMetrics.PrimaryDisplayHeight);

            if (GameOptions.Resolution.X < NativeResolution.X || GameOptions.Resolution.Y < NativeResolution.Y)
            {
                Settings->SetFullscreenMode(EWindowMode::Windowed);
            }
            else
            {
                Settings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
            }
            
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

// Steam Functions ---------------------------------------------------------------------------------------------------------------------------------------------
void UBUGameInstance::OnInventoryResultReady(SteamInventoryResultReady_t* Callback)
{
    if (Callback->m_handle != PendingResultHandle)
    {
        return;
    }

    if (Callback->m_result == EResult::k_EResultOK)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Inventory Operation Successful"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Warning: Failed Steam Inventory Operation, Error Code: %d"), Callback->m_result));
        // UE_LOG(LogSteamInventory, Warning, TEXT("Failed Steam Inventory Operation, Error Code: %d"), Callback->m_result)
    }

    if (bPendingRemove)
    {
        bPendingRemove = false;
        USteamFunctionLibrary::RemoveInventoryItem(this, static_cast<int64>(Callback->m_handle), PendingRemoveItemID, PendingRemoveQuantity);
        PendingRemoveItemID = 0;
        PendingRemoveQuantity = 0;
    }

    if (bPendingUniqueAdd)
    {
        bPendingUniqueAdd = false;
        USteamFunctionLibrary::AddInventoryItem(this, static_cast<int64>(Callback->m_handle), PendingUniqueAddItemID, PendingUniqueAddQuantity, true);
        PendingUniqueAddItemID = 0;
        PendingUniqueAddQuantity = 0;
    }

    // Destroy the handle to prevent memory leaks
    SteamInventory()->DestroyResult(PendingResultHandle);
    PendingResultHandle = k_SteamInventoryResultInvalid;
}

void UBUGameInstance::OnConsumeResultReady(SteamInventoryResultReady_t* Callback)
{
    if (Callback->m_handle != ConsumeResultHandle)
    {
        return;
    }

    if (Callback->m_result == EResult::k_EResultOK)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Item Consumption Successful"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Warning: Failed Item Consumption, Error Code: %d"), Callback->m_result));
    }

    // Destroy the handle to prevent memory leaks
    SteamInventory()->DestroyResult(ConsumeResultHandle);
    ConsumeResultHandle = k_SteamInventoryResultInvalid;
}

void UBUGameInstance::AddRecentlyConsumedItem(SteamItemInstanceID_t InstanceID, int32 ItemID)
{
    RecentlyConsumedItems.Add(InstanceID, ItemID);

    FTimerHandle TimerHandle;
    FTimerDelegate TimerDel;
    TimerDel.BindUObject(this, &UBUGameInstance::RemoveRecentlyConsumedItem, InstanceID);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 60.0f, false);
}

void UBUGameInstance::RemoveRecentlyConsumedItem(SteamItemInstanceID_t InstanceID)
{
    RecentlyConsumedItems.Remove(InstanceID);
}

void UBUGameInstance::AddRecentlyAddedItemType(int32 ItemID)
{
    RecentlyAddedItemTypes.AddUnique(ItemID);

    FTimerHandle TimerHandle;
    FTimerDelegate TimerDel;
    TimerDel.BindUObject(this, &UBUGameInstance::RemoveRecentlyAddedItemType, ItemID);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 60.0f, false);
}

void UBUGameInstance::RemoveRecentlyAddedItemType(int32 ItemID)
{
    RecentlyAddedItemTypes.Remove(ItemID);
}