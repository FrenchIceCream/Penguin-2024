// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControl.generated.h"

class UBuildingModeComponent;
class UInputMappingContext;

UCLASS()
class PENGUIN_API APlayerControl : public APlayerController
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) 
    UBuildingModeComponent* BuildingMode;
public:
    APlayerControl();	

    FVector GetMouseLocationOnTerrain() const;

protected:
    virtual void BeginPlay() override;
};


