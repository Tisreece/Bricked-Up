// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_KillZone.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInterface_KillZone : public UInterface
{
	GENERATED_BODY()
};

class BRICKEDUP_API IInterface_KillZone
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Kill Zone") void HitKillZone();
	
};
