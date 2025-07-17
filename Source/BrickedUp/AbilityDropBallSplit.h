#pragma once

#include "CoreMinimal.h"
#include "AbilityDrop.h"

#include "AbilityDropBallSplit.generated.h"

UCLASS()
class BRICKEDUP_API AAbilityDropBallSplit : public AAbilityDrop
{
    GENERATED_BODY()

 public:
    AAbilityDropBallSplit();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Ball Split") TSubclassOf<UAbilityComponentMaster> SplitComponent;
    
    UFUNCTION(BlueprintCallable, Category="Ability|Ball Split") void ApplyComponents();
};