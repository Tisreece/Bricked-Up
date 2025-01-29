// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

//#include "PlayerPaddle.h"

#include "BU_PlayerController.generated.h"

class APlayerPaddle;

//
//

UCLASS()
class BRICKEDUP_API ABU_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	ABU_PlayerController();

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player") APlayerPaddle* PlayerPaddle;
	
};
