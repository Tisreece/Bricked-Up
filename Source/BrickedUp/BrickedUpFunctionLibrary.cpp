#include "BrickedUpFunctionLibrary.h"
#include "Ball.h"
#include "Kismet/GameplayStatics.h"

void UBrickedUpFunctionLibrary::PlayBallHitAudio(AActor* HitActor, USoundBase* HitAudioToPlay)
{
    if (HitActor && HitAudioToPlay)
    {
        UGameplayStatics::PlaySoundAtLocation(HitActor, HitAudioToPlay, HitActor->GetActorLocation());
    }
}

FText UBrickedUpFunctionLibrary::FormatRichText(FString Syntax, FString Text)
{
    FString Result = FString::Printf(TEXT("<%s>%s</>"), *Syntax, *Text);
    return FText::FromString(Result);
}