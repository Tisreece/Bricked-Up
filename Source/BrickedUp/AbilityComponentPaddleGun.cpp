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
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Ammo: %f"), Ammo));
}

void UAbilityComponentPaddleGun::RemoveAbility()
{
    APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(GetOwner());
    if (PlayerPaddle)
    {
        PlayerPaddle->SetGunVisibility(false);
    }
    DestroyComponent();
}

void UAbilityComponentPaddleGun::AddAmmo(float AmountToAdd)
{
    Ammo += AmountToAdd;
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Ammo: %f"), Ammo));
}

bool UAbilityComponentPaddleGun::HasAmmo() const
{
    return Ammo > 0;
}

void UAbilityComponentPaddleGun::FireGun()
{
    Ammo -= 1.0f;
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Ammo: %f"), Ammo));

    if (!HasAmmo())
    {
        RemoveAbility();
    }
}