#include "SteamFunctionLibrary.h"
#include "BUGameInstance.h"

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
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Warning: Failed to Generate Item %d"), ItemID));
        return;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Successfully added %d of Item %d to inventory"), Quantity, ItemID));
    }
}