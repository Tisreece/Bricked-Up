#pragma once

#include "CoreMinimal.h"
#include "BrickMaster.h"

#include "BrickSmashable.generated.h"

UCLASS()
class BRICKEDUP_API ABrickSmashable : public ABrickMaster
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    ABrickSmashable();

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material") UMaterialInstanceDynamic* DynMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio") USoundBase* HealthLossAudio = nullptr;

    //Functions
    UFUNCTION(BlueprintCallable, Category = "Brick|Health") void SetNewMaterial();
};