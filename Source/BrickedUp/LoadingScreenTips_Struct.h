#pragma once

#include "CoreMinimal.h"
#include "LoadingScreenTips_Struct.generated.h"

USTRUCT(BlueprintType)
struct FLoadingScreenTip : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loading Screen") UTexture2D* Image;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loading Screen") FString Title;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Loading Screen") FString Description;
};
