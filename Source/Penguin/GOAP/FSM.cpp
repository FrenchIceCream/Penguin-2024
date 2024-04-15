// Fill out your copyright notice in the Description page of Project Settings.
#include "FSM.h"
#include "../MyCharacter.h"
#include "GoapAgent.h"
// Sets default values
UFSM::UFSM()
{
}

void UFSM::StateTick(UGoapAgent* GoapAgent, UGoalPlanner* Planner, AMyCharacter *Agent)
{
	//UE_LOG(LogTemp, Warning, TEXT("Ticking FSM StateTick"));
	if (!Stack.IsEmpty() && IsValid(Agent))
		if (IState* state = Cast<IState>(Stack.Top()))
			state->PerformState(GoapAgent, this, Planner, Agent);
}