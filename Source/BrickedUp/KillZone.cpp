// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AKillZone::AKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Scene Components
	KillCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Kill Collision"));
	RootComponent = KillCollision;
	KillCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	KillMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Kill Mesh"));
	KillMesh->SetupAttachment(KillCollision);
	KillMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

