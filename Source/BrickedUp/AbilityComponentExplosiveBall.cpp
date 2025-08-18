#include "AbilityComponentExplosiveBall.h"
#include "Ball.h"
#include "BrickMaster.h"

UAbilityComponentExplosiveBall::UAbilityComponentExplosiveBall()
{
    OverridesBrickHit = true;
    MaxLevel = 1;
    Unique = true;
}

void UAbilityComponentExplosiveBall::SetBallMaterial()
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (Ball && BallMaterial)
    {
        Ball->Ball->SetMaterial(0, BallMaterial);
    }
}

void UAbilityComponentExplosiveBall::ResetBallMaterial(UMaterial* ResetMaterial)
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (Ball && ResetMaterial)
    {
        Ball->Ball->SetMaterial(0, ResetMaterial);
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