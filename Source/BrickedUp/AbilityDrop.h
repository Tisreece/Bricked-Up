// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface_KillZone.h"

#include "AbilityDrop.generated.h"

class APlayerPaddle;
class UAbilityComponentMaster;

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

	UFUNCTION() void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component") class UStaticMeshComponent* DropMesh;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") float Speed = 50.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement") FVector Velocity = FVector(0.0f, 0.0f, -1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability") bool InstantEffect = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability") bool AppliesComponent = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability", meta = (ToolTip = "Determines whether or not this ability can level up and down")) 
		bool CanLevelUp = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability|Stats", meta = (ToolTip = "Whether or not the drop triggers a level up or down")) 
		bool AbilityLevelUp = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability") TSubclassOf<UAbilityComponentMaster> AbilityComponentToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh") UMaterialInterface* UpgradeMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh") UMaterialInterface* DowngradeMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh") UMaterialInterface* NeutralMaterial;

	//Functions
	UFUNCTION(BlueprintCallable, Category="Movement") void ApplyPhysics(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category="Ability") void HitPlayer(APlayerPaddle* PlayerPaddle);
	UFUNCTION(BlueprintCallable, Category="Ability|Stats") void SetRandomStats();
	UFUNCTION(BlueprintCallable, Category="Mesh") void SetMaterial();

	//Events
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Ability") void TriggerInstantAbility(APlayerPaddle* PlayerPaddle);

	//Interface
	virtual void HitKillZone_Implementation() override;

};
