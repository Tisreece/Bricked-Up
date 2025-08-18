#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AbilityComponentMaster.generated.h"

UCLASS(ClassGroup = (Ability), meta = (BlueprintSpawnableComponent), Blueprintable)
class BRICKEDUP_API UAbilityComponentMaster : public UActorComponent
{
    GENERATED_BODY()

public:
    UAbilityComponentMaster();

protected:
    virtual void BeginPlay() override;

public:

    //Variables    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Stats") int Level = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Stats") int MaxLevel = 5;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Stats") int StartingLevel = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Stats") bool Unique = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability") FName Name = "Default Name";
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability") bool RequiresStartingLevelOverride = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability") bool OverridesBrickHit = false;

    //Events
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Ability|Trigger") void TriggerEffect();
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Ability|Trigger") void ChangeLevel(int NewLevel);
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Ability|Destroy") void RemoveComponent();
};