#include "BrickedUpFunctionLibrary.h"
#include "Ball.h"
#include "Kismet/GameplayStatics.h"

void UBrickedUpFunctionLibrary::PlayBallHitAudio(ABall* Ball, USoundBase* HitAudioToPlay)
{
    if (Ball)
    {
        if (Ball->HitAudioOverride == nullptr)
        {
            UGameplayStatics::PlaySoundAtLocation(Ball, HitAudioToPlay, Ball->GetActorLocation());
        }
        else
        {
            // Play the hit audio of the ball
        }
    }
}

FText UBrickedUpFunctionLibrary::FormatRichText(FString Syntax, FString Text)
{
    FString Result = FString::Printf(TEXT("<%s>%s</>"), *Syntax, *Text);
    return FText::FromString(Result);
}