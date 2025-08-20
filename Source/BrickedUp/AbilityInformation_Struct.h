#pragma once

#include "CoreMinimal.h"
#include "AbilityInformation_Struct.generated.h"

USTRUCT(BlueprintType)
struct FAbilityInformation_Struct
{
    GENERATED_USTRUCT_BODY()

public:
    
    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability") FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability") UTexture2D* AbilityImage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability") bool CanLevelUp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability") bool AbilityLevelUp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability") bool Rare;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Audio") USoundBase* AbilityTriggerAudio;
};