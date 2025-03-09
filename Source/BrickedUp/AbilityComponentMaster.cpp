#include "AbilityComponentMaster.h"

UAbilityComponentMaster::UAbilityComponentMaster()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UAbilityComponentMaster::BeginPlay()
{
    Super::BeginPlay();

    TriggerEffect();
}