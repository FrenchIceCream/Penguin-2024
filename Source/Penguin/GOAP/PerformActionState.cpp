// Fill out your copyright notice in the Description page of Project Settings.


#include "PerformActionState.h"
#include "FSM.h"
#include "../MyCharacter.h"

void UPerformActionState::PerformState(UFSM* fsm, AMyCharacter *agent)
{
    UE_LOG(LogTemp, Warning, TEXT("PerformActionState: Performing state"));
}
