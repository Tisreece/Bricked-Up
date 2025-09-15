#include "MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::PlayMainMenuMusic()
{
    if (MainMenuMusic)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            MainMenuMusicComponent = UGameplayStatics::SpawnSound2D(this, MainMenuMusic, 1.0f, 1.0f, 0.0f, nullptr, true);
        }
    }  
}

