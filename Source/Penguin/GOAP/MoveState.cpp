// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveState.h"
#include "FSM.h"
#include "../MyCharacter.h"

void UMoveState::PerformState(UFSM* fsm, UGoalPlanner* Planner, AMyCharacter *agent)
{
    UE_LOG(LogTemp, Warning, TEXT("UMoveState: Performing state"));
}
