// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface_KillZone.h"

#include "AbilityDrop.generated.h"

class APlayerPaddle;

UCLASS()
class BRICKEDUP_API AAbilityDrop : public AActor,
public IInterface_KillZone
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityDrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* DropMesh;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") float Speed = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") FVector Velocity = FVector(0.0f, 0.0f, -1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Type") bool InstantEffect = true;

	//Functions
	UFUNCTION(BlueprintCallable, Category="Movement") void ApplyPhysics(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category="Ability") void HitPlayer(APlayerPaddle* PlayerPaddle);

	//Events
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Ability") void TriggerInstantAbility(APlayerPaddle* PlayerPaddle);

	//Interface
	virtual void HitKillZone_Implementation() override;

};
