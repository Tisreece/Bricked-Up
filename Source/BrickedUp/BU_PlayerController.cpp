// Fill out your copyright notice in the Description page of Project Settings.


#include "BU_PlayerController.h"

#include "PlayerPaddle.h"

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

