#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EndTrigger.generated.h"

UCLASS()
class BRICKEDUP_API AEndTrigger : public AActor

{
    GENERATED_BODY()

public:
    AEndTrigger();

    //Components
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") class USceneComponent* Root;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") class UBoxComponent* CollisionBox;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components") class UStaticMeshComponent* TriggerMesh;
};