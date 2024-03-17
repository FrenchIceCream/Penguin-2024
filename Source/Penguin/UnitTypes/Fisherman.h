// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MyCharacter.h"
#include "Fisherman.generated.h"

UCLASS()
class PENGUIN_API AFisherman : public AMyCharacter
{
	GENERATED_BODY()

	//bool IsFishing = false;
	int FishCount = 0;

public:
	void AddCaughtFish() {FishCount++;}
	int GetFishCount() {return FishCount;}
	void EmptyFishCount() {FishCount = 0;}
	void CatchFish();	
};
