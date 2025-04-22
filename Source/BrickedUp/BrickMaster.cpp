// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickMaster.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Ball.h"
#include "BU_GameMode.h"
#include "AbilityDrop.h"

#include "Interface_KillZone.h"

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
	Health = MaxHealth;
	
}

// Called every frame
void ABrickMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrickMaster::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherActor->IsA(ABall::StaticClass()))
	{
		HitEffect();
	}
}

void ABrickMaster::AddScore(float ScoreToAdd, float& NewScore)
{
	ABU_GameMode* GameMode = Cast<ABU_GameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		GameMode->AddScore(ScoreToAdd);
		NewScore = GameMode->Score;
	}
}

void ABrickMaster::DropAbility(TSubclassOf<AAbilityDrop> Drop)
{
	if (Drop)
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.X = 35.0f;
		FRotator SpawnRotation = FRotator(0.0f, -90.0f, 0.0f);
		FTransform SpawnTransform(SpawnRotation, SpawnLocation);

		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AAbilityDrop>(Drop, SpawnTransform, SpawnParams);
	}
}

void ABrickMaster::DestroyBrick()
{
	float NewValue = 0.0f;
	TSubclassOf<AAbilityDrop> DropClass;
	bool ShouldDrop = false;
	
	AddScore(Value, NewValue);

	ABU_GameMode* GameMode = Cast<ABU_GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GetDrop(DropClass, ShouldDrop);
		if (ShouldDrop)
		{
			DropAbility(DropClass);
		}
	}

	Destroy();
}

void ABrickMaster::TakeHealth()
{
	if (MaxHealth > 0)
	{
		Health--;
		if (Health <= 0)
		{
			DestroyBrick();
		}
	}
}

//Interface
void ABrickMaster::HitKillZone_Implementation()
{

}

