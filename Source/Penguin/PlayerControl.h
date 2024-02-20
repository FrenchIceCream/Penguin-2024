// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BuildingSystem/BuildingModeComponent.h"
#include "PlayerControl.generated.h"

UCLASS()
class PENGUIN_API APlayerControl : public APlayerController
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) 
    UBuildingModeComponent* BuildingMode;
public:
    APlayerControl();	

protected:
    virtual void BeginPlay() override;
};


