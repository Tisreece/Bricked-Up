#include "AbilityDropReverseControls.h"
#include "PlayerPaddle.h"

AAbilityDropReverseControls::AAbilityDropReverseControls()
{
    InstantEffect = true;
    AppliesComponent = false;
    CanLevelUp = false;
    Rare = true;
    AbilityLevelUp = false;
}

void AAbilityDropReverseControls::ReverseMovementControls(AActor* TargetActor)
{
    if (TargetActor)
    {
        APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(TargetActor);
        if (PlayerPaddle)
        {
            PlayerPaddle->MovementMultiplier *= -1.0f;
        }
    }

    DestroyDrop();
}