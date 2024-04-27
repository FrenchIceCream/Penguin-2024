// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Action_GetFood.generated.h"

UCLASS()
class PENGUIN_API UAction_GetFood : public UAction
{
	GENERATED_BODY()
	
	UPROPERTY()
	bool IsActionDone = false;

	UPROPERTY()
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
public:
	UAction_GetFood();

	bool CheckProceduralPrecondition(AMyCharacter* Agent) override;
	bool Perform(AMyCharacter* Agent) override;
	void Reset() override;
	
	bool RequiresInRange() override {	return true;	}
	bool IsDone() override;

	UFUNCTION()
	void AddFood(AMyCharacter * Agent);

	FVector GetTargetLocation() override 
	{
		FVector Origin, BoxExtent;
		Target->GetActorBounds(true, Origin, BoxExtent);
		return Origin + (BoxExtent + FVector(100, 100, 100)) * (-Target->GetActorRightVector());
	}
};
