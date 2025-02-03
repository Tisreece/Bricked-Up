// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "PlayerPaddle.generated.h"

UCLASS()
class BRICKEDUP_API APlayerPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* Paddle;
	
	
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Paddle") float Speed; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Paddle") FVector CurrentVelocity;
	
	//Functions
	UFUNCTION(BlueprintCallable, Category="Input") void SetPlayerController();
	UFUNCTION(BlueprintCallable, Category="Input") void MovePaddle(float X);

private: 


};
