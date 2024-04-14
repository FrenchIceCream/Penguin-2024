// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveState.h"
#include "FSM.h"
#include "../MyCharacter.h"
#include "Action.h"
#include "GoapAgent.h"
#include "FSM.h"
#include "GoalPlanner.h"
#include "IdleState.h"


void UMoveState::PerformState(UGoapAgent *GoapAgent, UFSM *fsm, UGoalPlanner *Planner, AMyCharacter *agent)
{
    //UE_LOG(LogTemp, Warning, TEXT("UMoveState: Performing state"));

    UAction *action = GoapAgent->GetCurrentActions()[0];
    if (action->RequiresInRange() && action->Target == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("No Target for Action"));
        fsm->PopState();
        fsm->PopState();
        auto state = NewObject<UIdleState>();
        fsm->PushState(state);
        return;
    }

    if (agent->MoveToTarget(action))
        fsm->PopState();
}
