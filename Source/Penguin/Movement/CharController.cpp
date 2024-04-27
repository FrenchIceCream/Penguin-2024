// Fill out your copyright notice in the Description page of Project Settings.


#include "CharController.h"
#include "NavigationSystem.h"
#include "../GOAP/Action.h"

bool ACharController::MoveToTarget(APawn *Agent, UAction *Action)
{
    if (!IsValid(Agent) || !IsValid(Action))
        return false;
    MoveToLocation(Action->GetTargetLocation(), -1, false, true, false, true);

    //UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), FVector::Distance(Agent->GetActorLocation(), Action->GetTargetLocation()));

    if (FVector::Distance(Agent->GetActorLocation(), 
        Action->GetTargetLocation()) < 100)
    {
        Action->SetInRange(true);
        return true;
    }

    return false;
}

void ACharController::CheckIfAIWorks()
{
    //UE_LOG(LogTemp, Warning, TEXT("AI WORKS"));

    MoveToLocation(FVector(0, 0, 0), -1, false);
}
