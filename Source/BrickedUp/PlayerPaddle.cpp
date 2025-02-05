// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"
#include "BU_PlayerController.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Scene Components
	USceneComponent* DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	Paddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle"));
	Paddle->SetupAttachment(DefaultSceneRoot);

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

	Paddle->AddLocalOffset(Movement, true);
}

void APlayerPaddle::AscendPaddle()
{
	FVector Movement(0.0f, 0.0f, AscendSpeed * GetWorld()->GetDeltaSeconds());

	AddActorWorldOffset(Movement, true);
}

