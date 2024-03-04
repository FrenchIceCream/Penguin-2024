// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildMenuWidget.h"
#include "Components/ListView.h"
#include "Components/Border.h"
#include "Engine/AssetManager.h"
#include "../PlayerControl.h"
#include "../BuildingSystem/BuildingDataAsset.h"
#include "../BuildingSystem/BuildingModeComponent.h"


void UBuildMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (MenuBorder)
    {
        MenuBorder->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UBuildMenuWidget::DisplayBuildMenu()
{
    if (!BuildingItemsList)
        return;

    verify ((AssetManager = UAssetManager::GetIfValid()) != nullptr);
    verify ((PlayerController = Cast<APlayerControl>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) != nullptr);
    verify ((BuildingMode = UBuildingModeComponent::FindBuildingModeComponent(PlayerController)) != nullptr);

    BuildingItemsList->ClearListItems();

    const TArray<FPrimaryAssetId> BuildingItemsDataAssets = BuildingMode->GetBuildingData();
    UE_LOG(LogTemp, Error, TEXT("%d"), BuildingItemsDataAssets.Num());
    for (int i = 0; i < BuildingItemsDataAssets.Num(); i++)
    {
        if (UBuildingDataAsset* BuildingData = Cast<UBuildingDataAsset>(AssetManager->GetPrimaryAssetObject(BuildingItemsDataAssets[i])))
            BuildingItemsList->AddItem(BuildingData);
    }

    BuildingItemsList->SetVisibility(ESlateVisibility::Visible);
    MenuBorder->SetVisibility(ESlateVisibility::Visible);

    if (BuildingMode && !BuildingMode->OnBuildModeEnterEvent.IsBound())
    {
        BuildingMode->OnBuildModeEnterEvent.AddDynamic(this, &UBuildMenuWidget::OnBuildModeEnteredEvent);
    }
}

void UBuildMenuWidget::HideBuildMenu() const
{
    BuildingItemsList->ClearListItems();
    BuildingItemsList->SetVisibility(ESlateVisibility::Hidden);
    MenuBorder->SetVisibility(ESlateVisibility::Hidden);

    if (BuildingMode && BuildingMode->OnBuildModeEnterEvent.IsBound())
    {
        BuildingMode->OnBuildModeEnterEvent.RemoveDynamic(this, &UBuildMenuWidget::OnBuildModeEnteredEvent);
    }
}

void UBuildMenuWidget::OnBuildModeEnteredEvent()
{
    HideBuildMenu();
}
