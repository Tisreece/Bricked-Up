// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface_KillZone.h"

#include "BrickMaster.generated.h"

class AAbilityDrop;

UCLASS()
class BRICKEDUP_API ABrickMaster : public AActor, public IInterface_KillZone
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrickMaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UBoxComponent* BrickCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* Brick;

	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Scoring") float Value = 10.0f;

	//Functions
	UFUNCTION(BlueprintCallable, Category="Hit") 
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, Category="Scoring") void AddScore(float ScoreToAdd, float& NewScore);

	UFUNCTION(BlueprintCallable, Category="Drop") void DropAbility(TSubclassOf<AAbilityDrop> Drop);
	
	//Events
	UFUNCTION(BlueprintImplementableEvent, Category="Hit") void HitEffect();

	//Interface
	virtual void HitKillZone_Implementation() override;

};
