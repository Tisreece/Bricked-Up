#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LuckTrigger.generated.h"

UCLASS()
class BRICKEDUP_API ALuckTrigger : public AActor
{
    GENERATED_BODY()
 
protected:
    virtual void BeginPlay() override;

public:
    ALuckTrigger();

    virtual void Tick(float DeltaTime) override;

    //Components
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UBoxComponent* TriggerCollision;

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Luck") float GlobalLuckAmount = 5.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Luck") float GlobalAbilityLuckAmount = 5.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger") bool Triggered = false;

    //Functions
    UFUNCTION(BlueprintCallable, Category="Ability|Luck") void ApplyNewLuck();
};