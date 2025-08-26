#include "Ceiling.h"
#include "Components/BoxComponent.h"
#include "Interface_HitCeiling.h"
#include "Ball.h"
#include "BrickedUpFunctionLibrary.h"

ACeiling::ACeiling()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;
    CollisionBox->SetCollisionProfileName(TEXT("BlockAllDynamic"));

    OnActorBeginOverlap.AddDynamic(this, &ACeiling::OnOverlapBegin);
    CollisionBox->OnComponentHit.AddDynamic(this, &ACeiling::OnHit);
}

void ACeiling::BeginPlay()
{
    Super::BeginPlay();
}

void ACeiling::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACeiling::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OtherActor && (OtherActor != this))
    {
        if (OtherActor->GetClass()->ImplementsInterface(UInterface_HitCeiling::StaticClass()))
        {
            IInterface_HitCeiling::Execute_HitCeiling(OtherActor);
        }
    }
}

void ACeiling::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && (OtherActor != this))
    {
        if (OtherActor->IsA(ABall::StaticClass()))
        {
            ABall* Ball = Cast<ABall>(OtherActor);
            {
                if (Ball)
                {
                    UBrickedUpFunctionLibrary::PlayBallHitAudio(Ball, HitAudio);
                }
            }
        }
    }
}
