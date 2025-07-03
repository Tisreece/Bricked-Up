// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickMaster.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Ball.h"
#include "BU_GameMode.h"
#include "AbilityDrop.h"
#include "PlayerPaddle.h"

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
	OnActorBeginOverlap.AddDynamic(this, &ABrickMaster::OnOverlapBegin);
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
		BallHit = Cast<ABall>(OtherActor);
		HitEffect();
	}
}

void ABrickMaster::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor->IsA(APlayerPaddle::StaticClass()))
	{
		ABU_GameMode* GameMode = Cast<ABU_GameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->BrickHitPlayer();
		}
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

	DestroyMesh();
}

void ABrickMaster::DestroyMesh()
{
	if (DestructionGC)
	{
		SpawnDestructionMesh();
	}
	else
	{
		Destroy();
	}
}

void ABrickMaster::SpawnDestructionMesh()
{
	UGeometryCollectionComponent* GCComp = NewObject<UGeometryCollectionComponent>(this);
	GCComp->SetRestCollection(DestructionGC);
	GCComp->SetWorldTransform(GetActorTransform());
	GCComp->AttachToComponent(BrickCollision, FAttachmentTransformRules::KeepWorldTransform);

	GCComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GCComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	GCComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GCComp->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);
	GCComp->SetGenerateOverlapEvents(false);
	GCComp->SetMobility(EComponentMobility::Movable);

	GCComp->RegisterComponent();
	
	GCComp->SetSimulatePhysics(true);
	GCComp->SetEnableGravity(false);
	
	AddInstanceComponent(GCComp);
	
	GCComp->Activate();

	Brick->SetVisibility(false);
	Brick->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BrickCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABrickMaster::DestructionCleanup, 5.0f, false);
}

void ABrickMaster::DestructionCleanup()
{
	Destroy();
}

void ABrickMaster::TakeHealth(bool& ToBeDestroyed)
{
	if (MaxHealth > 0)
	{
		Health--;
		if (Health <= 0)
		{
			ToBeDestroyed = true;
			DestroyBrick();
		}
		else
		{
			ToBeDestroyed = false;
		}
	}
	else
	{
		ToBeDestroyed = false;
	}
}

void ABrickMaster::FindNeighbouringBricks(TArray<ABrickMaster*>& NeighbouringBricks)
{
	// Set initial parameters for checking to the left
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * -20.0f; //Forward because the brick is rotated
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	// Line trace to the Left
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
	if (bHit)
	{
		if (ABrickMaster* HitBrickLeft = Cast<ABrickMaster>(HitResult.GetActor()))
		{
			NeighbouringBricks.Add(HitBrickLeft);
		}
	}

	// Set params for checking to the right
	End = Start + GetActorForwardVector() * 20.0f;

	// Line trace to the Right
	bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
	if (bHit)
	{
		if (ABrickMaster* HitBrickRight = Cast<ABrickMaster>(HitResult.GetActor()))
		{
			NeighbouringBricks.Add(HitBrickRight);
		}
	}

	// Set params for checking above
	End = Start + GetActorUpVector() * 5.0f;

	// Line trace above
	bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
	if (bHit)
	{
		if (ABrickMaster* HitBrickAbove = Cast<ABrickMaster>(HitResult.GetActor()))
		{
			NeighbouringBricks.Add(HitBrickAbove);
		}
	}

	// Set params for checking below
	End = Start + GetActorUpVector() * -5.0f;

	// Line trace below
	bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
	if (bHit)
	{
		if (ABrickMaster* HitBrickBelow = Cast<ABrickMaster>(HitResult.GetActor()))
		{
			NeighbouringBricks.Add(HitBrickBelow);
		}
	}
}

//Interface
void ABrickMaster::HitKillZone_Implementation()
{
	DestroyMesh();
}

