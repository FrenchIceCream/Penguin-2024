// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Action_Fishing.generated.h"

UCLASS()
class PENGUIN_API UAction_Fishing : public UAction
{
	GENERATED_BODY()

	UPROPERTY()
	int TimerCalls = 5;

	UPROPERTY()
	bool IsActionDone = false;

	UPROPERTY()
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
public:
	UAction_Fishing();

	bool CheckProceduralPrecondition(AMyCharacter* Agent) override;
	bool Perform(AMyCharacter* Agent) override;
	void Reset() override;
	
	bool RequiresInRange() override {	return true;	}
	bool IsDone() override;

	UFUNCTION()
	void AddFish(AMyCharacter * Agent);

	FVector GetTargetLocation() override 
	{
		// FVector MinMeshBounds, MaxMeshBounds;
		// Target->GetActorBounds(true, MinMeshBounds, MaxMeshBounds);
		return Target->GetActorLocation() + FVector(0,5,0);
	};
};
