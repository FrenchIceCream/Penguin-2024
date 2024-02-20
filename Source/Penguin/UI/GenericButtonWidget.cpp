// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericButtonWidget.h"

void UGenericButtonWidget::NativePreConstruct()
{   
    Super::NativePreConstruct();

    if (ButtonTextBlock)
        ButtonTextBlock->SetText(FText::FromString(ButtonText));
}
