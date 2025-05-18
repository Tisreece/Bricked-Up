#include "WallZone.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Ball.h"
#include "BrickedUpFunctionLibrary.h"

AWallZone::AWallZone()
{
    PrimaryActorTick.bCanEverTick = true;

    //Scene Components
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    Box1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box1"));
    Box1->SetupAttachment(Root);
    Box1->SetCollisionProfileName(TEXT("BlockAllDynamic"));

    Box2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box2"));
    Box2->SetupAttachment(Root);
    Box2->SetCollisionProfileName(TEXT("BlockAllDynamic"));

    //Bind Events
    Box1->OnComponentHit.AddDynamic(this, &AWallZone::OnHit);
    Box2->OnComponentHit.AddDynamic(this, &AWallZone::OnHit);

}

void AWallZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWallZone::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
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