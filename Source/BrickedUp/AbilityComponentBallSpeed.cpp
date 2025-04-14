#include "AbilityComponentBallSpeed.h"
#include "Ball.h"

void UAbilityComponentBallSpeed::SetBallSpeed(int32 NewLevel)
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (Ball)
    {
        float* NewSpeed = BallSpeedLevels.Find(NewLevel);
        Ball->Speed = *NewSpeed;
    }
}