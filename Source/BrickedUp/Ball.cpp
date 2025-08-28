// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerPaddle.h"
#include "Components/BoxComponent.h"
#include "AbilityComponentMaster.h"

#include "Interface_KillZone.h"

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

	BallCollision->OnComponentHit.AddDynamic(this, &ABall::OnHit);

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	if (ShouldStartAttached && PlayerPaddle)
	{
		AttachToPaddle(PlayerPaddle);
	}
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsAttached)
	{
		ApplyPhysics(DeltaTime);
	}
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->IsA(APlayerPaddle::StaticClass()))
		{
			// Hit Player Paddle
			APlayerPaddle* Paddle = Cast<APlayerPaddle>(OtherActor);
			if (Paddle)
			{
				FVector LocalHit = Paddle->PaddleCollision->GetComponentTransform().InverseTransformPosition(Hit.ImpactPoint);
				float HalfWidth = Paddle->PaddleCollision->GetUnscaledBoxExtent().X;
				float LocalX = LocalHit.X;

				float HitExtent = FMath::Clamp(LocalX / HalfWidth, -1.0f, 1.0f);

				ReflectMovement(true, Hit.Normal, HitExtent);
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABall::CanHitPlayerReset, 0.2f, false);
			}
		}
		else if (OtherActor->IsA(ABall::StaticClass()))
		{
			// Hit Another Ball
			ABall* OtherBall = Cast<ABall>(OtherActor);
			if (OtherBall)
			{
				BallCollision->IgnoreActorWhenMoving(OtherBall, true);
			}
		}
		else
		{
			ReflectMovement(false, Hit.Normal, 0.0f);
		}
	}
}

void ABall::ApplyPhysics(float DeltaTime)
{
	Velocity = Velocity.GetSafeNormal() * Speed;
	FRotator Rotation = RotationRate * Speed;

	AddActorWorldOffset(Velocity * DeltaTime, true);
	Ball->AddLocalRotation(Rotation * DeltaTime, true);
}

void ABall::ReflectMovement(bool HitPlayer, FVector HitNormal, float HitExtent)
{
	if (HitPlayer)
	{
		if (CanHitPlayer)
		{
			Velocity = Velocity.MirrorByVector(HitNormal);
			float FixedHitExtent = HitExtent * -1.0f;

			Velocity.Y += FixedHitExtent * MomentumInfluenceFactor;
			Velocity.Z += PlayerVelocityBoost;
			CanHitPlayer = false;
		}
		AddActorWorldOffset(HitNormal * PlayerImpactOffset, true);
	}
	else
	{
		Velocity = Velocity.MirrorByVector(HitNormal);
	}
	RotationRate *= -1;
}

void ABall::AttachToPaddle(APlayerPaddle* Paddle)
{
	if (Paddle)
	{
		//AttachToActor(Paddle, FAttachmentTransformRules::KeepRelativeTransform);
		AttachToComponent(Paddle->PaddleCollision, FAttachmentTransformRules::KeepWorldTransform);
		IsAttached = true;
	}
}

void ABall::DetachFromPaddle(APlayerPaddle* Paddle)
{
	if (Paddle)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		IsAttached = false;
	}
}

void ABall::GetBrickHitOverridingComponent(UAbilityComponentMaster*& OverridingComponent) const
{
	for (UActorComponent* Component : GetComponents())
	{
		if (Component->IsA(UAbilityComponentMaster::StaticClass()))
		{
			UAbilityComponentMaster* AbilityComponent = Cast<UAbilityComponentMaster>(Component);
			if (AbilityComponent && AbilityComponent->OverridesBrickHit)
			{
				OverridingComponent = AbilityComponent;
				return;
			}
		}
	}
	OverridingComponent = nullptr;
}

void ABall::GetComponentWithInterface(TSubclassOf<UInterface> Interface, UAbilityComponentMaster*& OverridingComponent) const
{
	OverridingComponent = nullptr;

	for (UActorComponent* Component : GetComponents())
	{
		if (Component->GetClass()->ImplementsInterface(Interface))
		{
			UAbilityComponentMaster* AbilityComponent = Cast<UAbilityComponentMaster>(Component);
			if (AbilityComponent)
			{
				OverridingComponent = AbilityComponent;
				return;
			}
		}
	}
}

//Interfaces
void ABall::HitKillZone_Implementation()
{

}

//Timers
void ABall::CanHitPlayerReset()
{
	CanHitPlayer = true;
}