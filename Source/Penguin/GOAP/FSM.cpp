// Fill out your copyright notice in the Description page of Project Settings.
#include "FSM.h"
#include "../MyCharacter.h"

// Sets default values
UFSM::UFSM()
{
}

void UFSM::StateTick(AMyCharacter *Agent)
{
	if (!Stack.IsEmpty())
	{
		if (IState* state = Cast<IState>(Stack.Top()))
			state->PerformState(this, Agent);
	}
}