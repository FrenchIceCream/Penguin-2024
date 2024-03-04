// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "BuildMenuWidget.generated.h"

class UListView;
class APlayerControl;
class UBuildingModeComponent;
class UAssetManager;
class UBorder;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildItemSelectedDelegate);
/**
 * 
 */
UCLASS(Abstract)
class PENGUIN_API UBuildMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UBorder* MenuBorder;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UListView * BuildingItemsList;

	UFUNCTION()
	void DisplayBuildMenu();

	UFUNCTION()
	void HideBuildMenu() const;

	FOnBuildItemSelectedDelegate OnBuildItemSelectedEvent;

protected:
	UFUNCTION()
	void OnBuildModeEnteredEvent();

	UPROPERTY()
	APlayerControl* PlayerController;

	UPROPERTY()
	UBuildingModeComponent* BuildingMode;

	UPROPERTY()
	UAssetManager* AssetManager;
};
