#include "AbilityComponentBallSplit.h"
#include "Ball.h"

void UAbilityComponentBallSplit::SplitBall()
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (Ball)
    {
        FVector SpawnLocation = Ball->GetActorLocation();
        FRotator SpawnRotation = Ball->GetActorRotation();
        FTransform SpawnTransform(SpawnRotation, SpawnLocation);
        FActorSpawnParameters SpawnParams;

        ABall* NewBall = GetWorld()->SpawnActor<ABall>(Ball->GetClass(), SpawnTransform, SpawnParams);
        FVector NewVelocity = Ball->Velocity;
        NewVelocity.Y = NewVelocity.Y * -1.0f;
        NewBall->Velocity = NewVelocity;
    }
}