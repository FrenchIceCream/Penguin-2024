// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "State.h"
#include "IdleState.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_API UIdleState : public UObject, public IState
{
	GENERATED_BODY()
	
public:
	void PerformState(UFSM* fsm, AMyCharacter* agent);
};
