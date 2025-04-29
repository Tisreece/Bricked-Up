#include "AbilityComponentPaddleSize.h"
#include "Components/BoxComponent.h"
#include "PlayerPaddle.h"

void UAbilityComponentPaddleSize::SetPaddleSize(int32 NewLevel)
{
    APlayerPaddle* Paddle = Cast<APlayerPaddle>(GetOwner());
    if (Paddle)
    {
        FVector* NewSize = PaddleSizeLevels.Find(NewLevel);
        Paddle->PaddleCollision->SetWorldScale3D(*NewSize);
    }
}