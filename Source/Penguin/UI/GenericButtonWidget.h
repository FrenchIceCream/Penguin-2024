// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "GenericButtonWidget.generated.h"

UCLASS()
class PENGUIN_API UGenericButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ButtonTextBlock;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FString ButtonText;
};
