// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuWidget.h"

void UGameMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (BuildButton)
    {
        BuildButton->Button->OnClicked.AddDynamic(this, &UGameMenuWidget::ToggleBuildMenu);
        if (BuildMenuWidget)
        {
            BuildMenuWidget->SetVisibility(ESlateVisibility::Hidden);
            bBuildMenuOpen = false;
            BuildMenuWidget->OnBuildItemSelectedEvent.AddDynamic(this, &UGameMenuWidget::OnBuildItemSelected);
        }
    }
}


void UGameMenuWidget::ToggleBuildMenu()
{
    bBuildMenuOpen = !bBuildMenuOpen;

    if (BuildMenuWidget)
    {   
        BuildMenuWidget->SetVisibility(bBuildMenuOpen ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

        bBuildMenuOpen ? BuildMenuWidget->DisplayBuildMenu() : BuildMenuWidget->HideBuildMenu();
    }
}

void UGameMenuWidget::OnBuildItemSelected()
{
    ToggleBuildMenu();
}