#include "AbilityDropDeath.h"
#include "BU_GameMode.h"

AAbilityDropDeath::AAbilityDropDeath()
{
    InstantEffect = true;
    AppliesComponent = false;
    CanLevelUp = false;
    Rare = true;
    AbilityLevelUp = false;
}

void AAbilityDropDeath::Die()
{
    if (ABU_GameMode* GameMode = Cast<ABU_GameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->LoseGame();
    }
    DestroyDrop();
}
