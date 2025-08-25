// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "Interface_Fire.h"

#include "BU_PlayerController.generated.h"

class APlayerPaddle;

//
//

UCLASS()
class BRICKEDUP_API ABU_PlayerController : public APlayerController , public IInterface_Fire
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	ABU_PlayerController();

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player") APlayerPaddle* PlayerPaddle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI|Pause") TSubclassOf<UUserWidget> PauseMenuClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI|Pause") UUserWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input") UInputMappingContext* InputMapping;

	//Functions
	UFUNCTION(BlueprintCallable, Category="Setup") void SetCursorAndInput();

	UFUNCTION(BlueprintCallable, Category="UI|Pause") void PauseMenuHandler(bool Open);
	UFUNCTION(BlueprintCallable, Category="Input") void SetDebugInputs(UInputAction* EscapeAction);
	
};
