// Fill out your copyright notice in the Description page of Project Settings.


#include "PerformActionState.h"
#include "FSM.h"
#include "../MyCharacter.h"
#include "Action.h"
#include "GoapAgent.h"
#include "FSM.h"
#include "GoalPlanner.h"
#include "IdleState.h"
#include "MoveState.h"

void UPerformActionState::PerformState(UGoapAgent* GoapAgent, UFSM* fsm, UGoalPlanner* Planner, AMyCharacter *agent)
{
    //UE_LOG(LogTemp, Warning, TEXT("PerformActionState: Performing state"));
    if (GoapAgent->GetCurrentActions()->IsEmpty())
    {
        fsm->PopState();
        fsm->PushState(NewObject<UIdleState>());
        return;
    }

    UAction* action = *GoapAgent->GetCurrentActions()->Peek();

    if (action->IsDone())
        GoapAgent->GetCurrentActions()->Pop();

    if (!GoapAgent->GetCurrentActions()->IsEmpty())
    {
        action = *GoapAgent->GetCurrentActions()->Peek();
        bool InRange = action->RequiresInRange() ? action->IsInRange() : true;

        if (InRange)
        {
            if (!action->Perform(agent))
            {
                fsm->PopState();
                fsm->PushState(NewObject<UIdleState>());
            }
        }
        else 
        {
            fsm->PushState(NewObject<UMoveState>());
        }
    }
    else
    {
        fsm->PopState();
        fsm->PushState(NewObject<UIdleState>());
    }
}
