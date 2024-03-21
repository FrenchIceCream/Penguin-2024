// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "State.generated.h"

class UFSM;
class AMyCharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UState : public UInterface
{
	GENERATED_BODY()
};

class PENGUIN_API IState
{
	GENERATED_BODY()
public:
	void PerformState(UFSM* fsm, AMyCharacter* agent);
};
