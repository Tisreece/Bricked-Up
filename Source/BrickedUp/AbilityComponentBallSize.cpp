#include "AbilityComponentBallSize.h"
#include "Ball.h"

void UAbilityComponentBallSize::SetBallSize(int32 NewLevel)
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (Ball)
    {
        FVector* NewScale = BallSizeLevels.Find(NewLevel);
        Ball->SetActorScale3D(*NewScale);
    }
}