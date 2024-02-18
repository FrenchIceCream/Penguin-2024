// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../PlayerControl.h"
#include "HUDWidget.generated.h"

UCLASS()
class PENGUIN_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	APlayerControl * PlayerController;
};
