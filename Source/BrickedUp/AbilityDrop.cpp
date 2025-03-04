// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityDrop.h"
#include "Components/StaticMeshComponent.h"

#include "Interface_KillZone.h"

// Sets default values
AAbilityDrop::AAbilityDrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Scene Components
	DropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drop Mesh"));
	RootComponent = DropMesh;
	DropMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void AAbilityDrop::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAbilityDrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ApplyPhysics(DeltaTime);
}

void AAbilityDrop::ApplyPhysics(float DeltaTime)
{
	Velocity = Velocity.GetSafeNormal() * Speed;
	
	AddActorWorldOffset(Velocity * DeltaTime, true);
}

//Interfaces
void AAbilityDrop::HitKillZone_Implementation()
{

}

