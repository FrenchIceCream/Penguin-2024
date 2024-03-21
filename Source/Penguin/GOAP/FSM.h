// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "FSM.generated.h"

class AMyCharacter;

UCLASS()
class PENGUIN_API UFSM : public UObject
{
	GENERATED_BODY()

	TArray<IState*> Stack;
public:	
	// Sets default values for this actor's properties
	UFSM();

	void StateTick(AMyCharacter* Agent);

	void PushState(IState* state) {Stack.Push(state);}
	void PopState() {Stack.Pop();}
};