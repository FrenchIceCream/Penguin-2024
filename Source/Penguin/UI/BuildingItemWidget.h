// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GenericButtonWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../PlayerControl.h"
#include "../BuildingSystem/BuildingDataAsset.h"
#include "../BuildingSystem/BuildingModeComponent.h"
#include "BuildingItemWidget.generated.h"

UCLASS()
class PENGUIN_API UBuildingItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UGenericButtonWidget* PlaceBuildingButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	UImage* Image;

protected:
	UFUNCTION()
	void OnPlaceBuildingItemSelected();

	//это из IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY()
	APlayerControl* PlayerController;

	UPROPERTY()
	UBuildingDataAsset* BuildingData; 

	UPROPERTY()
	UBuildingModeComponent* BuildingMode; 
};
