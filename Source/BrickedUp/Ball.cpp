// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Scene Components
	USceneComponent* DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	Ball->SetupAttachment(DefaultSceneRoot);

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ApplyPhysics(DeltaTime);

}

void ABall::ApplyPhysics(float DeltaTime)
{
	Velocity.Z += Gravity * DeltaTime;

	FHitResult Hit;
	AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);

	if (Hit.IsValidBlockingHit())
    {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, "Hit");
        // Reflect the velocity along the hit surface's normal (bounce)
        Velocity = FVector::VectorPlaneProject(Velocity, Hit.Normal);
    }
}

