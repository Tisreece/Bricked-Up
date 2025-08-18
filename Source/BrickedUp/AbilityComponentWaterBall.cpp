#include "AbilityComponentWaterBall.h"
#include "Ball.h"

UAbilityComponentWaterBall::UAbilityComponentWaterBall()
{
    MaxLevel = 1;
    Unique = true;
}

void UAbilityComponentWaterBall::SetBallMaterial()
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (BallMaterial)
    {
        Ball->Ball->SetMaterial(0, BallMaterial);
    }
}
