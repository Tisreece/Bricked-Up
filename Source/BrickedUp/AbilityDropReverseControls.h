#pragma once

#include "CoreMinimal.h"
#include "AbilityDrop.h"

#include "AbilityDropReverseControls.generated.h"

class AActor;

UCLASS()
class BRICKEDUP_API AAbilityDropReverseControls : public AAbilityDrop
{
	GENERATED_BODY()

public:
	AAbilityDropReverseControls();

    //Functions
    UFUNCTION(BlueprintCallable, Category="Ability|ReverseControls") void ReverseMovementControls(AActor* TargetActor);
};
