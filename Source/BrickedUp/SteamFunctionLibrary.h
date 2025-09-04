#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "steam/steam_api.h"
#include "steam/isteaminventory.h"

#include "SteamFunctionLibrary.generated.h"

UCLASS()
class BRICKEDUP_API USteamFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Steam|Inventory System") static void AddInventoryItem(UObject* WorldContextObject, int32 ItemID, int32 Quantity = 1);
};