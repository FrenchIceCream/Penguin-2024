// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GenericButtonWidget.h"
#include "BuildMenuWidget.h"
#include "GameMenuWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PENGUIN_API UGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UGenericButtonWidget* BuildButton;

	UPROPERTY(meta = (BindWidget))
	UBuildMenuWidget * BuildMenuWidget;

protected:
	UFUNCTION()
	void ToggleBuildMenu();

	UFUNCTION()
	void OnBuildItemSelected();

	UPROPERTY()
	bool bBuildMenuOpen = false;
};
