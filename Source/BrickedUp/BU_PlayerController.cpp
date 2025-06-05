#include "BU_PlayerController.h"

#include "PlayerPaddle.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

//Sets default values
ABU_PlayerController::ABU_PlayerController()
{
    PrimaryActorTick.bCanEverTick = true;

}

void ABU_PlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void ABU_PlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABU_PlayerController::SetCursorAndInput()
{
    bShowMouseCursor = false;
    SetInputMode(FInputModeGameOnly());
}

void ABU_PlayerController::PauseMenuHandler(bool Open)
{
    if (PauseMenuClass)
    {
        if (Open)
        {
            UGameplayStatics::SetGamePaused(GetWorld(), true);
            DisableInput(this);

            PauseMenu = CreateWidget<UUserWidget>(this, PauseMenuClass);
            PauseMenu->AddToViewport();
            bShowMouseCursor = true;

            FInputModeGameAndUI InputMode;
            InputMode.SetWidgetToFocus(PauseMenu->TakeWidget());
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            SetInputMode(InputMode);
        }
        else
        {
            UGameplayStatics::SetGamePaused(GetWorld(), false);
            EnableInput(this);

            PauseMenu->RemoveFromParent();
            PauseMenu = nullptr;
            bShowMouseCursor = false;

            SetInputMode(FInputModeGameOnly());
        }
    }
}

