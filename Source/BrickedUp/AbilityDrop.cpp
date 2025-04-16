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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DropMeshFinder(TEXT("/Game/Abilities/Drops/AbilityDrop"));
	if (DropMeshFinder.Succeeded()) DropMesh->SetStaticMesh(DropMeshFinder.Object);

	ImagePlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Image Plane"));
	ImagePlane->SetupAttachment(DropMesh);
	ImagePlane->SetCollisionProfileName(TEXT("NoCollision"));
	ImagePlane->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	ImagePlane->SetRelativeLocation(FVector(0.0f, 2.0f, 0.0f));
	ImagePlane->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ImagePlaneFinder(TEXT("/Engine/BasicShapes/Plane"));
	if (ImagePlaneFinder.Succeeded()) ImagePlane->SetStaticMesh(ImagePlaneFinder.Object);
	
	OnActorBeginOverlap.AddDynamic(this, &AAbilityDrop::OnOverlapBegin);

	//Set Material Defaults
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> UpgradeMatFinder(TEXT("/Game/Abilities/Drops/AbilityDropUpgrade_Mat"));
	if(UpgradeMatFinder.Succeeded())
	{
		UpgradeMaterial = UpgradeMatFinder.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DowngradeMatFinder(TEXT("/Game/Abilities/Drops/AbilityDropDowngrade_Mat"));
	if(DowngradeMatFinder.Succeeded())
	{
		DowngradeMaterial = DowngradeMatFinder.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> NeutralMatFinder(TEXT("/Game/Abilities/Drops/AbilityDropNeutral_Mat"));
	if(NeutralMatFinder.Succeeded())
	{
		NeutralMaterial = NeutralMatFinder.Object;
	}
}

// Called when the game starts or when spawned
void AAbilityDrop::BeginPlay()
{
	Super::BeginPlay();

	SetRandomStats();
	SetMaterial();
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
		PlayerPaddle->AbilityInformation = AbilityInformation;
		if(CanLevelUp)
		{
			PlayerPaddle->AbilityLevelUp = AbilityLevelUp;
		}
		else
		{
			PlayerPaddle->AbilityLevelUp = true;
		}
		PlayerPaddle->AbilityChanged.Broadcast();
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

void AAbilityDrop::SetMaterial()
{
	if(AbilityLevelUp)
	{
		if(UpgradeMaterial)
		{
			DropMesh->SetMaterial(0, UpgradeMaterial);
		}
	}
	else
	{
		if(DowngradeMaterial)
		{
			DropMesh->SetMaterial(0, DowngradeMaterial);
		}
	}
}

//Interfaces
void AAbilityDrop::HitKillZone_Implementation()
{

}

