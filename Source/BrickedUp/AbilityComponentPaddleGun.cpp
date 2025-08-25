#include "AbilityComponentPaddleGun.h"
#include "PlayerPaddle.h"
#include "PaddleGunBullet.h"

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
    SpawnBullets();
    Ammo -= 1.0f;
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Ammo: %f"), Ammo));

    if (!HasAmmo())
    {
        RemoveAbility();
    }
}

void UAbilityComponentPaddleGun::SpawnBullets()
{
    APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(GetOwner());
    if (PlayerPaddle)
    {
        FRotator SpawnRotation = PlayerPaddle->GetActorRotation();

        FVector SpawnLocation1 = PlayerPaddle->Gun1->GetComponentLocation();
        FTransform SpawnTransform1(SpawnRotation, SpawnLocation1);
        FVector SpawnLocation2 = PlayerPaddle->Gun2->GetComponentLocation();
        FTransform SpawnTransform2(SpawnRotation, SpawnLocation2);
        FActorSpawnParameters SpawnParams;

        APaddleGunBullet* Bullet1 = GetWorld()->SpawnActor<APaddleGunBullet>(BulletClass, SpawnTransform1, SpawnParams);
        APaddleGunBullet* Bullet2 = GetWorld()->SpawnActor<APaddleGunBullet>(BulletClass, SpawnTransform2, SpawnParams);
    }
}