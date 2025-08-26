#include "AbilityComponentPaddleGun.h"
#include "PlayerPaddle.h"
#include "PaddleGunBullet.h"
#include "Kismet/GameplayStatics.h"

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
        PlayerPaddle->AmmoChanged.Broadcast();
    }
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
    APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(GetOwner());
    if (PlayerPaddle)
    {
        PlayerPaddle->AmmoChanged.Broadcast();
    }
}

bool UAbilityComponentPaddleGun::HasAmmo() const
{
    return Ammo > 0;
}

void UAbilityComponentPaddleGun::FireGun()
{
    SpawnBullets();
    UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetOwner()->GetActorLocation());
    Ammo -= 1.0f;
    APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(GetOwner());
    if (PlayerPaddle)
    {
        PlayerPaddle->AmmoChanged.Broadcast();
    }

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