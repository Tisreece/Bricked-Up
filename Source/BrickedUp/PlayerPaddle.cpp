// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BU_GameMode.h"

#include "BU_PlayerController.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Scene Components
	PaddleRoot = CreateDefaultSubobject<UBoxComponent>(TEXT("Paddle Root"));
	RootComponent = PaddleRoot;
	PaddleRoot->SetBoxExtent(FVector(0.1f, 0.1f, 0.1f));
	PaddleRoot->SetCollisionProfileName(TEXT("NoCollision"));

	PaddleCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Paddle Collision"));
	PaddleCollision->SetupAttachment(PaddleRoot);
	PaddleCollision->SetBoxExtent(FVector(10.0f, 1.25f, 1.25f));
	PaddleCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	Paddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle"));
	Paddle->SetupAttachment(PaddleCollision);
	Paddle->SetCollisionProfileName(TEXT("NoCollision"));
	
	PaddleOverlapCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Paddle Overlap Collision"));
	PaddleOverlapCollision->SetupAttachment(PaddleCollision);
	PaddleOverlapCollision->SetBoxExtent(FVector(9.8f, 1.5f, 1.5f));
	PaddleOverlapCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	//Variables
	Speed = 2.0f;

}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPaddle::SetPlayerController()
{
	AController* LocalController = GetController();

	APlayerController* LocalPlayerController = Cast<APlayerController>(LocalController);

	if (LocalPlayerController)
	{
		ABU_PlayerController* PlayerController = Cast<ABU_PlayerController>(LocalPlayerController);
		if (PlayerController)
		{
			PlayerController->PlayerPaddle = this;
		}
	}
}

void APlayerPaddle::MovePaddle(float X)
{
	FVector Movement(X * Speed * GetWorld()->GetDeltaSeconds(), 0.0f, 0.0f);

	//Get Current Velocity to effect Ball Movement
	CurrentVelocity = Movement / GetWorld()->GetDeltaSeconds();
	CurrentVelocity = CurrentVelocity * -1;

	PaddleCollision->AddLocalOffset(Movement, true);
}

void APlayerPaddle::AscendPaddle()
{
	FVector Movement(0.0f, 0.0f, AscendSpeed * GetWorld()->GetDeltaSeconds());

	AddActorWorldOffset(Movement, true);
}

void APlayerPaddle::SetInitialCheckpoint()
{
	PreviousCheckpoint = GetActorLocation().Z;
}

void APlayerPaddle::CheckNextCheckpoint(ABU_GameMode* GameMode, bool& CheckpointReached)
{
	if(!GameMode) return;
	
	float CurrentHeight = GetActorLocation().Z;
	float TargetHeight = PreviousCheckpoint + GameMode->CheckpointInterval;
	
	CheckpointReached = (CurrentHeight >= TargetHeight);
}

void APlayerPaddle::SetNextCheckpoint(ABU_GameMode* GameMode)
{
	float TargetHeight = PreviousCheckpoint + GameMode->CheckpointInterval;
	PreviousCheckpoint = TargetHeight;
}

void APlayerPaddle::AddScore(float ScoreToAdd, float& NewScore)
{
	ABU_GameMode* GameMode = Cast<ABU_GameMode>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		GameMode->AddScore(ScoreToAdd);
		NewScore = GameMode->Score;
	}
}
