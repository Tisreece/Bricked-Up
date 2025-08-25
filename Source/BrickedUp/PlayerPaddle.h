// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilityInformation_Struct.h"
#include "Interface_Fire.h"

#include "PlayerPaddle.generated.h"

class UAbilityComponentMaster;
class ABall;

//Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityChanged);


UCLASS()
class BRICKEDUP_API APlayerPaddle : public APawn , public IInterface_Fire
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* Gun1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* Gun2;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Paddle") float Speed; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement|Paddle") FVector CurrentVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Paddle") float MovementMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement|Ascend") float AscendSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Ascend") float AscendSpeedDefault = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement|Ascend") float SprintSpeed = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Scoring") float PreviousCheckpoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Scoring") float NextCheckpoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scoring") float CheckpointScore = 25.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ability") TSubclassOf<UAbilityComponentMaster> StoredAbility;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ability") FAbilityInformation_Struct AbilityInformation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio") USoundBase* PaddleHitAudio = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Audio") ABall* BallHit = nullptr;

	//Delegates
	UPROPERTY(BlueprintAssignable, Category="Ability") FAbilityChanged AbilityChanged;
	
	//Functions
	UFUNCTION(BlueprintCallable, Category="Input") void SetPlayerController();
	UFUNCTION(BlueprintCallable, Category="Input") void MovePaddle(float X);
	
	UFUNCTION(BlueprintCallable, Category="Movement") void SetSprint(bool Sprint);
	UFUNCTION(BlueprintCallable, Category="Movement") void AscendPaddle();

	UFUNCTION(BlueprintCallable, Category="Scoring") void SetInitialCheckpoint();
	UFUNCTION(BlueprintCallable, Category="Scoring") void CheckNextCheckpoint(ABU_GameMode* GameMode, bool& CheckpointReached);
	UFUNCTION(BlueprintCallable, Category="Scoring") void SetNextCheckpoint(ABU_GameMode* GameMode);
	UFUNCTION(BlueprintCallable, Category="Scoring") void AddScore(float ScoreToAdd, float& NewScore);

	UFUNCTION(BlueprintCallable, Category="Ability") void ApplyAbility(AActor* OtherActor);
	UFUNCTION(BlueprintCallable, Category="Ability") void RegisterNewAbilityComponent(ABall* Ball);
	UFUNCTION(BlueprintCallable, Category="Ability") void ExpendAbility();

	UFUNCTION(BlueprintCallable, Category="Component") void SetGunVisibility(bool Visible);

	UFUNCTION(BlueprintCallable, Category="Hit") void GetBallFromHit(AActor* OtherActor, bool& BallFound); //Call on hit in BP

private: 


};
