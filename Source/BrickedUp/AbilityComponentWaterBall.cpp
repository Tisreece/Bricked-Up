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

void UAbilityComponentWaterBall::ResetBallMaterial(UMaterial* ResetMaterial)
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (Ball && ResetMaterial)
    {
        Ball->Ball->SetMaterial(0, ResetMaterial);
    }
}

void UAbilityComponentWaterBall::TriggerGuardianAngelCheck()
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (Ball)
    {
        Ball->GuardianAngel();
    }
}

void UAbilityComponentWaterBall::SetIgnorePlayer()
{
    ABall* Ball = Cast<ABall>(GetOwner());
    if (Ball)
    {
        Ball->SetIgnorePlayer(true);
    }
}
