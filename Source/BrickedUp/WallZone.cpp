#include "WallZone.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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