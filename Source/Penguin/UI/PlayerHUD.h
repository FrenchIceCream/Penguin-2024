// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.h"
#include "PlayerHUD.generated.h"

UCLASS(Abstract)
class PENGUIN_API APlayerHUD : public AHUD
{
	GENERATED_BODY()



public:
	UFUNCTION()
	void CreateHUD();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|UI")
	TSubclassOf<UUserWidget> HudClass;

	APlayerHUD();
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY()
	UHUDWidget* HUD;

	virtual void BeginPlay();
};


