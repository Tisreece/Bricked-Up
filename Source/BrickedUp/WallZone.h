#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "WallZone.generated.h"

UCLASS()
class BRICKEDUP_API AWallZone : public AActor
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    AWallZone();

    virtual void Tick(float DeltaTime) override;

    //Components
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components") class USceneComponent* Root;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components") class UBoxComponent* Box1;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components") class UBoxComponent* Box2;
};