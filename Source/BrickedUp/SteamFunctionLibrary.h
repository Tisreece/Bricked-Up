#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "steam/steam_api.h"
#include "steam/isteaminventory.h"

#include "SteamFunctionLibrary.generated.h"

class UBUGameInstance;

UCLASS()
class BRICKEDUP_API USteamFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:

    //Ask for items    
    UFUNCTION(BlueprintCallable, Category="Steam|Inventory System") static void RequestInventoryRefresh();

    // Add Items
    UFUNCTION(BlueprintCallable, Category="Steam|Inventory System") static void RequestInventoryItemAdd(UObject* WorldContextObject, int32 ItemID, int32 Quantity = 1, bool Unique = true);
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Steam|Inventory System") static bool OwnsItemType(int32 ItemID, int64 ResultHandle, UBUGameInstance* GameInstance);
    UFUNCTION(BlueprintCallable, Category="Steam|Inventory System") static void AddInventoryItem(UObject* WorldContextObject, int64 ResultHandle, int32 ItemID, int32 Quantity = 1, bool Unique = true);

    //Remove Items
    UFUNCTION(BlueprintCallable, Category="Steam|Inventory System") static void RequestInventoryItemRemoval(UObject* WorldContextObject, int32 ItemID, int32 Quantity = 1);
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Steam|Inventory System") static int64 GetLastItemInstance(int32 ItemID, int64 ResultHandle, UBUGameInstance* GameInstance);
    UFUNCTION(BlueprintCallable, Category="Steam|Inventory System") static void RemoveInventoryItem(UObject* WorldContextObject, int64 ResultHandle, int32 ItemID, int32 Quantity = 1);
};