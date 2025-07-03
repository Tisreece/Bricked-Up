// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface_KillZone.h"
#include "GeometryCollection/GeometryCollectionObject.h"

#include "BrickMaster.generated.h"

class AAbilityDrop;
class ABall;

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

	UFUNCTION() void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UBoxComponent* BrickCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* Brick;

	//Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Scoring") float Value = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health") int MaxHealth = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health") int Health = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio") USoundBase* DestroyAudio = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Audio") ABall* BallHit = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh") UGeometryCollection* DestructionGC;

	//Functions
	UFUNCTION(BlueprintCallable, Category="Hit") 
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable, Category="Hit") void DestroyBrick();
	UFUNCTION(BlueprintCallable, Category="Hit") void DestroyMesh();
	UFUNCTION(BlueprintCallable, Category="Hit") void TakeHealth(bool& ToBeDestroyed);
	UFUNCTION(BlueprintCallable, Category="Hit") void FindNeighbouringBricks(TArray<ABrickMaster*>& NeighbouringBricks);
	
	UFUNCTION(BlueprintCallable, Category="Hit") void SpawnDestructionMesh();
	UFUNCTION() void DestructionCleanup();

	UFUNCTION(BlueprintCallable, Category="Scoring") void AddScore(float ScoreToAdd, float& NewScore);

	UFUNCTION(BlueprintCallable, Category="Drop") void DropAbility(TSubclassOf<AAbilityDrop> Drop);

	
	//Events
	UFUNCTION(BlueprintImplementableEvent, Category="Hit") void HitEffect();
	UFUNCTION(BlueprintImplementableEvent, Category="Destruction") void StartDestruction();

	//Interface
	virtual void HitKillZone_Implementation() override;

};
