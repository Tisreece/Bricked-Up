// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface_KillZone.h"
#include "Interface_HitBrick.h"

#include "Ball.generated.h"

class APlayerPaddle;
class UAbilityComponentMaster;

UCLASS()
class BRICKEDUP_API ABall : public AActor, public IInterface_KillZone, public IInterface_HitBrick
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category="Hit") 
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* Ball;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class USphereComponent* BallCollision;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") float Speed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") FVector Velocity = FVector(0.0f, 0.0f, 1.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") FRotator RotationRate = FRotator(5.0f, 0.0f, 0.0f);
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
	UFUNCTION(BlueprintCallable, Category="Movement") void ReflectMovement(bool HitPlayer, FVector HitNormal, float HitExtent);

	UFUNCTION(BlueprintCallable, Category="Attach") void AttachToPaddle(APlayerPaddle* Paddle);
	UFUNCTION(BlueprintCallable, Category="Attach") void DetachFromPaddle(APlayerPaddle* Paddle);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Hit") void GetBrickHitOverridingComponent(UAbilityComponentMaster*& OverridingComponent) const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Component") void GetComponentWithInterface(TSubclassOf<UInterface> Interface, UAbilityComponentMaster*& OverridingComponent) const;

	//Events
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Steam|Achievements") void GuardianAngel();

	//Timers
	UFUNCTION() void CanHitPlayerReset();

	//Interface
	virtual void HitKillZone_Implementation() override;

};
