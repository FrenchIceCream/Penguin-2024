// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "BuildingItemWidget.generated.h"

class UGenericButtonWidget;
class UImage;
class UTextBlock;
class UBuildingModeComponent;
class UBuildingDataAsset;
class APlayerControl;


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
	UFUNCTION(BlueprintCallable)
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
