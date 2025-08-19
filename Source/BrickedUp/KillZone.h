// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

UCLASS()
class BRICKEDUP_API AKillZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UBoxComponent* KillCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UBoxComponent* KillHitCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* KillMesh;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio") bool CanPlayKillAudio = true;

};
