// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "HUDWidget.generated.h"

class APlayerControl;
class UGameMenuWidget;

UCLASS()
class PENGUIN_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeOnInitialized() override;
protected:
	void CreateGameMenu();

	UPROPERTY()
	APlayerControl * PlayerController;

	UPROPERTY()
	UGameMenuWidget* GameMenuWidget;

	UPROPERTY()
	UWorld* WorldContext;
};
