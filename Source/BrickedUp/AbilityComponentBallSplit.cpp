#include "AbilityComponentBallSplit.h"
#include "Ball.h"
#include "Kismet/GameplayStatics.h"
#include "BUGameInstance.h"

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

        CheckTotalBalls();
    }
}

void UAbilityComponentBallSplit::CheckTotalBalls()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), FoundActors);

    int Count = FoundActors.Num();
    if (Count >= 50)
    {
        UBUGameInstance* GameInstance = Cast<UBUGameInstance>(GetWorld()->GetGameInstance());
        GameInstance->WriteAchievementProgress(TEXT("50BALLS_ACH"), 100.0f);
    }
}