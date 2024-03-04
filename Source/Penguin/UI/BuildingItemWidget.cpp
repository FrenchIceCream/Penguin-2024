// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingItemWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GenericButtonWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../PlayerControl.h"
#include "../BuildingSystem/BuildingDataAsset.h"
#include "../BuildingSystem/BuildingModeComponent.h"

void UBuildingItemWidget::NativeOnInitialized()
{
    if (PlaceBuildingButton)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Has Placebuilding Button"));
        PlaceBuildingButton->Button->OnClicked.AddDynamic(this, &UBuildingItemWidget::OnPlaceBuildingItemSelected);
    }

    verify ((PlayerController = Cast<APlayerControl>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) != nullptr);

    BuildingMode = UBuildingModeComponent::FindBuildingModeComponent(PlayerController);
}

void UBuildingItemWidget::OnPlaceBuildingItemSelected()
{
    UE_LOG(LogTemp, Warning, TEXT("Item Selected"));
    if (!BuildingMode)
    {
        UE_LOG(LogTemp, Error, TEXT("No Building Mode"));
        return;
    }
    
    BuildingMode->EnterBuildPlacementMode(BuildingData);
}

void UBuildingItemWidget::NativeOnListItemObjectSet(UObject *ListItemObject)
{
    IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

    BuildingData = Cast<UBuildingDataAsset>(ListItemObject);

    if (BuildingData)
    {
        TitleText->SetText(BuildingData->TitleText);
        Image->SetBrushFromTexture(BuildingData->Image.LoadSynchronous());
    }
}
