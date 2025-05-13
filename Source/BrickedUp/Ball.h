// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface_KillZone.h"

#include "Ball.generated.h"

class APlayerPaddle;

UCLASS()
class BRICKEDUP_API ABall : public AActor, public IInterface_KillZone
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* Ball;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class USphereComponent* BallCollision;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") float Speed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") FVector Velocity = FVector(0.0f, 0.0f, 1.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") float PlayerImpactOffset = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") float PlayerVelocityBoost = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") bool CanHitPlayer = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") float MomentumInfluenceFactor = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attach") APlayerPaddle* PlayerPaddle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attach") bool IsAttached = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attach") bool ShouldStartAttached = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio") USoundBase* HitAudioOverride = nullptr;

	//Functions
	UFUNCTION(BlueprintCallable, Category="Movement") void ApplyPhysics(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category="Movement") void ReflectMovement(bool HitPlayer, FVector HitNormal, FVector PaddleVelocity);

	UFUNCTION(BlueprintCallable, Category="Attach") void AttachToPaddle(APlayerPaddle* Paddle);
	UFUNCTION(BlueprintCallable, Category="Attach") void DetachFromPaddle(APlayerPaddle* Paddle);

	//Interface
	virtual void HitKillZone_Implementation() override;

};
