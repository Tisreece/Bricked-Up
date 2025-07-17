#include "AbilityDropBallSplit.h"
#include "Kismet/GameplayStatics.h"
#include "Ball.h"
#include "AbilityComponentMaster.h"

AAbilityDropBallSplit::AAbilityDropBallSplit()
{
    InstantEffect = true;
    AppliesComponent = false;
    CanLevelUp = false;
}

void AAbilityDropBallSplit::ApplyComponents()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), FoundActors);
    
    for (AActor* Actor : FoundActors)
    {
        if (ABall* Ball = Cast<ABall>(Actor))
        {
            UAbilityComponentMaster* SplitComponentInstance = NewObject<UAbilityComponentMaster>(Ball, SplitComponent);

            if (SplitComponentInstance)
            {
                SplitComponentInstance->RegisterComponent();
                SplitComponentInstance->SetComponentTickEnabled(true);
                Ball->AddInstanceComponent(SplitComponentInstance);
            }
        }
    }
    DestroyDrop();
}