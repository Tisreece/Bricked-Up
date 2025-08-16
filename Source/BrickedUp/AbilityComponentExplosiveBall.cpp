#include "AbilityComponentExplosiveBall.h"
#include "Ball.h"
#include "BrickMaster.h"

UAbilityComponentExplosiveBall::UAbilityComponentExplosiveBall()
{
    OverridesBrickHit = true;
    MaxLevel = 1;
}

void UAbilityComponentExplosiveBall::SetBallMaterial()
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (Ball && BallMaterial)
    {
        Ball->Ball->SetMaterial(0, BallMaterial);
    }
}

void UAbilityComponentExplosiveBall::Explode(TArray<ABrickMaster*> BricksToExplode)
{
    for (ABrickMaster* MarkedBrick : BricksToExplode)
    {
        if (MarkedBrick)
        {
            MarkedBrick->DestroyBrick();
        }
    }
}