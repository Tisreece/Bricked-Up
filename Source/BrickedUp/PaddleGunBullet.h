#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface_HitBrick.h"
#include "Interface_HitCeiling.h"

#include "PaddleGunBullet.generated.h"

UCLASS()
class BRICKEDUP_API APaddleGunBullet : public AActor, public IInterface_HitBrick, public IInterface_HitCeiling
{
    GENERATED_BODY()
protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    APaddleGunBullet();

    //Components
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* Mesh;

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") float Speed = 200.0f;

    //Functions
    UFUNCTION(BlueprintCallable, Category="Movement") void ApplyPhysics(float DeltaTime);

};