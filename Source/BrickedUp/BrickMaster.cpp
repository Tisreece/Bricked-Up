// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickMaster.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABrickMaster::ABrickMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Scene Components
	BrickCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Brick Collision"));
	RootComponent = BrickCollision;
	BrickCollision->SetBoxExtent(FVector(10.0f, 5.0f, 2.5f));
	BrickCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick"));
	Brick->SetupAttachment(BrickCollision);
	Brick->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Bind Events
	BrickCollision->OnComponentHit.AddDynamic(this, &ABrickMaster::OnHit);
}

// Called when the game starts or when spawned
void ABrickMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrickMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrickMaster::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		HitEffect();
	}
}

// void ABrickMaster::HitEffect()
// {

// }

