// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"
#include "HUDWidget.h"

void APlayerHUD::CreateHUD()
{
    if (HudClass)
    {
        HUD = CreateWidget<UHUDWidget>(GetWorld(), HudClass);
        if (HUD)
            HUD->AddToViewport();
    }
}

APlayerHUD::APlayerHUD()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APlayerHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();
}


