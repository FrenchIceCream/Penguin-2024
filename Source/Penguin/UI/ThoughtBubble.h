// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ThoughtBubble.generated.h"

class UImage;

UCLASS(Blueprintable)
class PENGUIN_API UThoughtBubble : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* BubbleImage;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setting Bubbles")
	void SetHungerImage();

	void TestLog() {UE_LOG(LogTemp, Error, TEXT("Testing Thought Bubble"));};
};
