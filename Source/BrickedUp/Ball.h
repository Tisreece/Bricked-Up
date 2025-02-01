// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class BRICKEDUP_API ABall : public AActor
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component", meta = (DisplayPriority = 2)) class UStaticMeshComponent* Ball;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class USphereComponent* BallCollision;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta = (DisplayPriority = 1)) float Speed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") FVector Velocity = FVector(0.0f, 0.0f, -1.0f);

	//Functions
	UFUNCTION(BlueprintCallable, Category="Movement") void ApplyPhysics(float DeltaTime);

};
