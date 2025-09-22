#include "BU_PlayerController.h"

#include "PlayerPaddle.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedActionKeyMapping.h"

//Sets default values
ABU_PlayerController::ABU_PlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
    bEnableClickEvents = true;
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

void ABU_PlayerController::SetDebugInputs(UInputAction* EscapeAction)
{
    if(InputMapping)
    {
        TArray<FEnhancedActionKeyMapping> Mappings = InputMapping->GetMappings();

        if(EscapeAction)
        {
            FEnhancedActionKeyMapping* EscapeMapping = Mappings.FindByPredicate(
                [EscapeAction](const FEnhancedActionKeyMapping& Mapping)
                {
                    return Mapping.Action == EscapeAction;
                }
            );

            if (EscapeMapping)
            {
                if(FPlatformMisc::IsPackagedForDistribution())
                {
                    InputMapping->UnmapAllKeysFromAction(EscapeMapping->Action);
                    InputMapping->MapKey(EscapeMapping->Action, EKeys::Escape);
                }
                else
                {
                    InputMapping->UnmapAllKeysFromAction(EscapeMapping->Action);
                    InputMapping->MapKey(EscapeMapping->Action, EKeys::P);
                }
            }
        }
    }
}

void ABU_PlayerController::TakeHighResScreenshot(int Width, int Height)
{
    // FString Command = FString::Printf(TEXT("HighResShot %dx%d showui"), Width, Height);
    // ConsoleCommand(Command, false);
    FString Timestamp = FDateTime::Now().ToString();
    FString Filename = FString::Printf(TEXT("Screenshot_%s.png"), *Timestamp);
    FScreenshotRequest::RequestScreenshot(Filename, false, false);
}

