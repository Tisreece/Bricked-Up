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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UBoxComponent* PaddleRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UBoxComponent* PaddleCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UBoxComponent* PaddleOverlapCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* Paddle;
	
	
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Paddle") float Speed; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Paddle") FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") float AscendSpeed = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Scoring") float PreviousCheckpoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Scoring") float NextCheckpoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring") float CheckpointScore = 25.0f;
	
	//Functions
	UFUNCTION(BlueprintCallable, Category="Input") void SetPlayerController();
	UFUNCTION(BlueprintCallable, Category="Input") void MovePaddle(float X);

	UFUNCTION(BlueprintCallable, Category="Movement") void AscendPaddle();

	UFUNCTION(BlueprintCallable, Category="Scoring") void SetInitialCheckpoint();
	UFUNCTION(BlueprintCallable, Category="Scoring") void CheckNextCheckpoint(ABU_GameMode* GameMode, bool& CheckpointReached);
	UFUNCTION(BlueprintCallable, Category="Scoring") void SetNextCheckpoint(ABU_GameMode* GameMode);
	UFUNCTION(BlueprintCallable, Category="Scoring") void AddScore(float ScoreToAdd, float& NewScore);

private: 


};
