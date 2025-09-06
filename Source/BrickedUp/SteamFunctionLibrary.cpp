#include "SteamFunctionLibrary.h"
#include "BUGameInstance.h"
#include "Async/Async.h"

void USteamFunctionLibrary::AddInventoryItem(UObject* WorldContextObject, int32 ItemID, int32 Quantity)
{
    UBUGameInstance* GameInstance = Cast<UBUGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());
    if (!SteamInventory())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Warning: Steam Inventory not initialized"));
        return;
    }
    if (!GameInstance)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Warning: Game Instance not found"));
        return;
    }

    SteamItemDef_t ItemDefID = static_cast<SteamItemDef_t>(ItemID);
    SteamInventoryResult_t ResultHandle = k_SteamInventoryResultInvalid;
    uint32 QuantityToAdd = static_cast<uint32>(Quantity);

    bool Success = SteamInventory()->GenerateItems(&ResultHandle, &ItemDefID, &QuantityToAdd, 1);
    GameInstance->PendingResultHandle = ResultHandle;
    if (!Success)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Warning: Failed to Generate Item %d"), ItemID));
        return;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Successfully added %d of Item %d to inventory"), Quantity, ItemID));
    }
}

int64 USteamFunctionLibrary::GetLastItemInstance(int32 ItemID, int64 ResultHandle, UBUGameInstance* GameInstance)
{

    if (!SteamInventory())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Warning: Steam Inventory not initialized"));
        return 0;
    }
    
    uint32 Count = 0;

    if(!SteamInventory()->GetResultItems(ResultHandle, nullptr, &Count))
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("No Steam Inventory Items found of ID"));
        return 0;
    }

    TArray<SteamItemDetails_t> Items;
    Items.SetNumUninitialized(Count);

    if (!SteamInventory()->GetResultItems(ResultHandle, Items.GetData(), &Count))
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Warning: Steam Inventory Item data retrieval failed"));
        return 0;
    }

    SteamItemInstanceID_t LastInstance = k_SteamItemInstanceIDInvalid;

    for (uint32 i = 0; i < Count; i++)
    {
        if (
            Items[i].m_iDefinition == ItemID && 
            Items[i].m_unQuantity > 0 &&
            !GameInstance->RecentlyConsumedItems.Contains(Items[i].m_itemId)
        )
        {
            LastInstance = Items[i].m_itemId;
        }
    }

    return static_cast<int64>(LastInstance);
}

void USteamFunctionLibrary::RemoveInventoryItem(UObject* WorldContextObject, int64 ResultHandle, int32 ItemID, int32 Quantity)
{
    UBUGameInstance* GameInstance = Cast<UBUGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());
    int64 InstanceID = GetLastItemInstance(ItemID, ResultHandle, GameInstance);
    if (InstanceID == k_SteamItemInstanceIDInvalid || InstanceID == 0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Warning: No instances of Item %d found in inventory"), ItemID));
        return;
    }
    
    if (!SteamInventory())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Warning: Steam Inventory not initialized"));
        return;
    }
    if (!GameInstance)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Warning: Game Instance not found"));
        return;
    }

    SteamInventoryResult_t ConsumeResultHandle = k_SteamInventoryResultInvalid;
    uint32 QuantityToRemove = static_cast<uint32>(Quantity);

    bool Success = SteamInventory()->ConsumeItem(&ConsumeResultHandle, static_cast<SteamItemInstanceID_t>(InstanceID), QuantityToRemove);
    GameInstance->ConsumeResultHandle = ConsumeResultHandle;
    if (!Success)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Warning: Failed to Remove Item %d"), InstanceID));
        return;
    }
    else
    {
        AsyncTask(ENamedThreads::GameThread, [GameInstance, InstanceID, ItemID, Quantity]()
        {
            GameInstance->AddRecentlyConsumedItem(static_cast<SteamItemInstanceID_t>(InstanceID), ItemID);
        });
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Successfully removed %d of Item %llu from inventory"), Quantity, static_cast<unsigned long long>(InstanceID)));
    }
}

void USteamFunctionLibrary::RequestInventoryItemRemoval(UObject* WorldContextObject, int32 ItemID, int32 Quantity)
{
    if (ItemID <=0)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Warning: ItemID must be greater than 0"));
        return;
    }

    UBUGameInstance* GameInstance = Cast<UBUGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());
    if (!SteamInventory() || !GameInstance)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Warning: Steam Inventory not initialized or Game Instance not found"));
        return;
    }
    GameInstance->bPendingRemove = true;
    GameInstance->PendingRemoveItemID = ItemID;
    GameInstance->PendingRemoveQuantity = Quantity;
    SteamInventory()->GetAllItems(&GameInstance->PendingResultHandle);
}