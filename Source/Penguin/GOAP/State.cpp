// Fill out your copyright notice in the Description page of Project Settings.

#include "State.h"
#include "FSM.h"
#include "../MyCharacter.h"
#include "GoalPlanner.h"
// Add default functionality here for any IState functions that are not pure virtual.

void IState::PerformState(UFSM * fsm, UGoalPlanner* Planner, AMyCharacter * agent)
{
}
