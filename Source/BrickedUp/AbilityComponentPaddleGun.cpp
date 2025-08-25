#include "AbilityComponentPaddleGun.h"
#include "PlayerPaddle.h"

UAbilityComponentPaddleGun::UAbilityComponentPaddleGun()
{
    MaxLevel = 1;
}

void UAbilityComponentPaddleGun::SetupAbility()
{
    Ammo = StartingAmmo;

    APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(GetOwner());
    if (PlayerPaddle)
    {
        PlayerPaddle->SetGunVisibility(true);
    }
}