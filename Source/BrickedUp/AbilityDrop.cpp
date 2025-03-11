// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityDrop.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerPaddle.h"

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
	
	OnActorBeginOverlap.AddDynamic(this, &AAbilityDrop::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AAbilityDrop::BeginPlay()
{
	Super::BeginPlay();

	SetRandomStats();
}

// Called every frame
void AAbilityDrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ApplyPhysics(DeltaTime);
}

void AAbilityDrop::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(OtherActor);
	if (PlayerPaddle)
	{
		HitPlayer(PlayerPaddle);
	}
}

void AAbilityDrop::ApplyPhysics(float DeltaTime)
{
	Velocity = Velocity.GetSafeNormal() * Speed;
	
	AddActorWorldOffset(Velocity * DeltaTime, true);
}

void AAbilityDrop::HitPlayer(APlayerPaddle* PlayerPaddle)
{
	if (InstantEffect)
	{
		if (AppliesComponent)
		{
			//Applies Component to Player
		}
		else
		{
			TriggerInstantAbility(PlayerPaddle);
		}
	}
	else
	{
		//For Stored Ability
		PlayerPaddle->StoredAbility = AbilityComponentToApply;
		if(CanLevelUp)
		{
			PlayerPaddle->AbilityLevelUp = AbilityLevelUp;
		}
		else
		{
			PlayerPaddle->AbilityLevelUp = true;
		}
		Destroy();
	}
}

void AAbilityDrop::SetRandomStats()
{
	if(CanLevelUp)
	{
		AbilityLevelUp = FMath::RandBool();
	}
}

//Interfaces
void AAbilityDrop::HitKillZone_Implementation()
{

}

