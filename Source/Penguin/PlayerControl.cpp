// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/PlayerHUD.h"
#include "PlayerControl.h"

APlayerControl::APlayerControl()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    BuildingMode = CreateDefaultSubobject<UBuildingModeComponent>(TEXT("BuildingModeComponent"));
}
FVector APlayerControl::GetMouseLocationOnTerrain() const
{
    FVector WorldLocation, WorldDirection;
    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
    FHitResult OutHit;
    if (GetWorld()->LineTraceSingleByChannel(OutHit, WorldLocation, WorldLocation + WorldDirection * 10000, ECollisionChannel::ECC_WorldStatic))
    {
        if (OutHit.bBlockingHit)
            return OutHit.Location;
    }
    return FVector::ZeroVector;
}
void APlayerControl::BeginPlay()
{   
    Super::BeginPlay();

    FInputModeGameAndUI InputMode;
    InputMode.SetHideCursorDuringCapture(false);
    SetInputMode(InputMode);
    bShowMouseCursor = true;

    if (APlayerHUD* Hud = Cast<APlayerHUD>(GetHUD()))
        Hud->CreateHUD();

    if (BuildingMode != nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Have Building Mode"));
        BuildingMode->LoadBuildingData();
    }
};