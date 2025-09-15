// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BRICKEDUP_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio") USoundBase* MainMenuMusic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio") UAudioComponent* MainMenuMusicComponent;

	//Functions
	UFUNCTION(BlueprintCallable, Category = "Audio") void PlayMainMenuMusic();

	//Events
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Audio") void FadeOutMainMenuMusic();
	
};
