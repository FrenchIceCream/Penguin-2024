// Fill out your copyright notice in the Description page of Project Settings.

#include "StatsBar.h"
#include "../MyCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UStatsBar::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (!OwnerChar.IsValid())
        return;

    HungerBar->SetPercent(OwnerChar->GetHunger() / 100.0f);    
    FNumberFormattingOptions options;
    options.SetMaximumFractionalDigits(0);
    CurrentHungerLabel->SetText(FText::AsNumber(OwnerChar->GetHunger(), &options));
}
