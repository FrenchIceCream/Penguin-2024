// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.h"
#include "MoveState.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_API UMoveState : public UObject, public IState
{
	GENERATED_BODY()
	
public:
	void PerformState(UFSM* fsm, UGoalPlanner* Planner, AMyCharacter* agent) override;
};
