// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleState.h"
#include "FSM.h"
#include "../MyCharacter.h"
#include "Action.h"
#include "GoapAgent.h"
#include "FSM.h"
#include "GoalPlanner.h"
#include "PerformActionState.h"

void UIdleState::PerformState(UGoapAgent* GoapAgent, UFSM* fsm, UGoalPlanner* Planner, AMyCharacter *agent)
{
    //UE_LOG(LogTemp, Warning, TEXT("IdleState: Performing state"));
    TMap<FString, bool> WorldState = agent->GetWorldState();
    TMap<FString, bool> Goal = agent->GetGoal();

    TQueue<UAction*>* path = Planner->FindBestPath(agent, GoapAgent->GetAvailableActions(), WorldState, Goal);
    if (path)
    {
        GoapAgent->SetCurrentActions(path);

        fsm->PopState();
        fsm->PushState(NewObject<UPerformActionState>());
    }
    else
    {
        fsm->PopState();
        fsm->PushState(NewObject<UIdleState>());
    }
}
