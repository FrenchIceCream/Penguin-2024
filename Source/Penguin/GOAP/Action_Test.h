// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Action_Test.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_API UAction_Test : public UAction
{
	GENERATED_BODY()

	bool DoneTesing = false;

	FTimerHandle TimerHandle;
	int TimerCalls = 3;

	void TestFunction();
public:

	UAction_Test();

	bool CheckProceduralPrecondition(AMyCharacter* Agent) override;
	bool Perform(AMyCharacter* Agent) override;
	
	bool RequiresInRange() override {	return true;	}
	bool IsDone() override {	return DoneTesing;	}
};
