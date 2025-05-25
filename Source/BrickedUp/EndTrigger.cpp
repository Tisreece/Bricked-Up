#include "EndTrigger.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AEndTrigger::AEndTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    //Scene Components
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
    CollisionBox->SetupAttachment(Root);
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger Mesh"));
    TriggerMesh->SetupAttachment(Root);
    TriggerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}