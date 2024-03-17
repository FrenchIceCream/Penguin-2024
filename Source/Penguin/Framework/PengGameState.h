// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "../BuildingSystem/BuildingType.h"
#include "PengGameState.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_API APengGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	APengGameState();
	virtual void Tick(float DeltaTime) override;
	void AddPlacedObject(const FWorldSelectableData NewObject)	{PlacedObjects.Add(NewObject);}
	void AddPenguin(AActor * NewObject)	{PlacedPenguins.Add(NewObject);}

	TArray<FWorldSelectableData> GetPlacedObjects() {return PlacedObjects;}
	TArray<AActor*> GetPlacedPenguins() {return PlacedPenguins;}
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<FWorldSelectableData> PlacedObjects;

	UPROPERTY()
	TArray<AActor*> PlacedPenguins;
};
