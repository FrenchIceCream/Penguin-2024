// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatsBar.generated.h"

class AMyCharacter;

UCLASS(Abstract)
class PENGUIN_API UStatsBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetOwnerChar(AMyCharacter* Char) {OwnerChar = Char;}
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	TWeakObjectPtr<AMyCharacter> OwnerChar;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HungerBar;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CurrentHungerLabel;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MaxHungerLabel;
};
