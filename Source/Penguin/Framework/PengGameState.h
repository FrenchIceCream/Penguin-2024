// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "../BuildingSystem/BuildingType.h"
#include "PengGameState.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_API APengGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	APengGameState();
	virtual void Tick(float DeltaTime) override;
	void AddPlacedObject(const FWorldSelectableData NewObject)	{PlacedObjects.Add(NewObject);}

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<FWorldSelectableData> PlacedObjects;
};
