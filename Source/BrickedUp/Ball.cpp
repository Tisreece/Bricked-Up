// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Scene Components
	BallCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Ball Collision"));
	RootComponent = BallCollision;

	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	Ball->SetupAttachment(BallCollision);


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
	Velocity = Velocity.GetSafeNormal() * Speed;
	
	AddActorWorldOffset(Velocity * DeltaTime, true);
}

void ABall::ReflectMovement(bool HitPlayer, FVector HitNormal)
{
	if (HitPlayer)
	{
		if (CanHitPlayer)
		{
			Velocity = Velocity.MirrorByVector(HitNormal);
			CanHitPlayer = false;
		}
		AddActorWorldOffset(HitNormal * PlayerImpactOffset, true);
	}
	else
	{
		Velocity = Velocity.MirrorByVector(HitNormal);
	}
}