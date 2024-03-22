// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleState.h"
#include "FSM.h"
#include "../MyCharacter.h"

void UIdleState::PerformState(UFSM* fsm, UGoalPlanner* Planner, AMyCharacter *agent)
{
    //UE_LOG(LogTemp, Warning, TEXT("IdleState: Performing state"));
    TMap<FString, bool> WorldState = agent->GetWorldState();
    TMap<FString, bool> Goal = agent->GetGoal();

    
}
