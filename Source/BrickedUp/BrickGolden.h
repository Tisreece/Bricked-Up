#pragma once

#include "CoreMinimal.h"
#include "BrickMaster.h"

#include "BrickGolden.generated.h"

UCLASS()
class BRICKEDUP_API ABrickGolden : public ABrickMaster
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    ABrickGolden();

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material") UMaterialInstanceDynamic* DynMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio") USoundBase* HealthLossAudio = nullptr;

    //Functions
    UFUNCTION(BlueprintCallable, Category = "Brick|Health") void SetNewMaterial();
};