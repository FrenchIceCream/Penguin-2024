// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"

#include "PlayerHUD.generated.h"

class UHUDWidget;

UCLASS(Abstract)
class PENGUIN_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void CreateHUD();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|UI")
	TSubclassOf<UUserWidget> GameMenuWidgetClass;

	APlayerHUD();
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY()
	UHUDWidget* HUD;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|UI")
	TSubclassOf<UUserWidget> HudClass;

	virtual void BeginPlay();
};


