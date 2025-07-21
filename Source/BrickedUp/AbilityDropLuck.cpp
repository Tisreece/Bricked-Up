#include "AbilityDropLuck.h"
#include "BU_GameMode.h"

AAbilityDropLuck::AAbilityDropLuck()
{
    InstantEffect = true;
    AppliesComponent = false;
    CanLevelUp = true;
    Rare = true;
}

void AAbilityDropLuck::AddLuckStats(TMap<TSubclassOf<AAbilityDrop>, float> AbilityList, float PositiveDropChance, float NegativeDropChance)
{
    ABU_GameMode* GameMode = Cast<ABU_GameMode>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;

    for (const TPair<TSubclassOf<AAbilityDrop>, float>& Ability : AbilityList)
    {
        TSubclassOf<AAbilityDrop> AbilityClass = Ability.Key;
        float ValueToAdd = Ability.Value;

        if (GameMode->DropList.Contains(AbilityClass))
        {
            GameMode->DropList[AbilityClass] += ValueToAdd;
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Error: Luck Ability found not matching Ability in the Game Mode"));
        }
    }

    GameMode->PositiveDropChance += PositiveDropChance;
    GameMode->NegativeDropChance += NegativeDropChance;

    DestroyDrop();
}