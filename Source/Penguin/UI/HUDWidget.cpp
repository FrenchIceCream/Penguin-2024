// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"
#include "HUDWidget.h"

void UHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    verify ((WorldContext = GetWorld()) != nullptr);
    verify ((PlayerController = Cast<APlayerControl>(UGameplayStatics::GetPlayerController(GetWorld(), 0))) != nullptr);

    CreateGameMenu();
}

void UHUDWidget::CreateGameMenu()
{
    if (!WorldContext || !PlayerController)
        return;
    
    if (const APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD()))
    {
        if (PlayerHUD->GameMenuWidgetClass)
        {
            GameMenuWidget = Cast<UGameMenuWidget>(CreateWidget(WorldContext, PlayerHUD->GameMenuWidgetClass));
            if (GameMenuWidget)
                GameMenuWidget->AddToViewport();
        }
    }
}
