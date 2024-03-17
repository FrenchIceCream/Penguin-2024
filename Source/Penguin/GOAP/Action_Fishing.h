// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Action_Fishing.generated.h"

class ABuilding;

UCLASS()
class PENGUIN_API UAction_Fishing : public UAction
{
	GENERATED_BODY()

	//Fisherman Hut
	ABuilding* TargetBuilding;
public:
	UAction_Fishing();

	bool CheckProceduralPrecondition(AMyCharacter* Agent) override;
};
