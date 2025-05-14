#pragma once

#include "CoreMinimal.h"
#include "BrickMaster.h"

#include "BrickSmashable.generated.h"

UCLASS()
class BRICKEDUP_API ABrickSmashable : public ABrickMaster
{
    GENERATED_BODY()

public:
    ABrickSmashable();

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Material") UMaterialInterface* HealthMaterial2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brick|Material") UMaterialInterface* HealthMaterial1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio") USoundBase* HealthLossAudio = nullptr;

    //Functions
    UFUNCTION(BlueprintCallable, Category = "Brick|Health") void SetNewMaterial();
};