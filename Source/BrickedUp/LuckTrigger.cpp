#include "LuckTrigger.h"

#include "Components/BoxComponent.h"
#include "BU_GameMode.h"
#include "AbilityDrop.h"

ALuckTrigger::ALuckTrigger()
{
    PrimaryActorTick.bCanEverTick = true;

    TriggerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Collision"));
    RootComponent = TriggerCollision;
    TriggerCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ALuckTrigger::BeginPlay()
{
    Super::BeginPlay();
}

void ALuckTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALuckTrigger::ApplyNewLuck()
{
    ABU_GameMode* GameMode = Cast<ABU_GameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode || Triggered) return;

    for (TPair<TSubclassOf<AAbilityDrop>, float>& Ability : GameMode->DropList)
    {
        Ability.Value += GlobalAbilityLuckAmount;
        GameMode->PositiveDropChance += GlobalLuckAmount;
        GameMode->NegativeDropChance += GlobalLuckAmount;
    }
}