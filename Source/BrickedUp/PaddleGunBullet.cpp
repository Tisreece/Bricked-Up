#include "PaddleGunBullet.h"
#include "Components/StaticMeshComponent.h"

APaddleGunBullet::APaddleGunBullet()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    Mesh->SetCollisionProfileName(TEXT("OverlapAll"));
}

void APaddleGunBullet::BeginPlay()
{
    Super::BeginPlay();
}

void APaddleGunBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ApplyPhysics(DeltaTime);
}

void APaddleGunBullet::ApplyPhysics(float DeltaTime)
{
    FVector Velocity = FVector(0.0f, 0.0f, 1.0f) * Speed;
    AddActorWorldOffset(Velocity * DeltaTime, true);
}

