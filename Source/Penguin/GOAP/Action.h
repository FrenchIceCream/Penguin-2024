// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

class AMyCharacter;

UCLASS(Abstract)
class PENGUIN_API UAction : public UObject
{
	GENERATED_BODY()

protected:
	TMap<FString, bool> Preconditions;
	TMap<FString, bool> Effects;

	bool ShouldBeInRange = false;
public:
	UAction();

	float ActionCost = 1.0f;
	AActor *Target;

	virtual bool CheckProceduralPrecondition(AMyCharacter* Agent) {	UE_LOG(LogTemp, Error, TEXT("CheckProceduralPrecondition: must be overriden")); return false;	}
	virtual bool Perform(AMyCharacter* Agent) {	UE_LOG(LogTemp, Error, TEXT("Perform: must be overriden")); return false;	}
	virtual bool RequiresInRange() {	UE_LOG(LogTemp, Error, TEXT("RequiresInRange: must be overriden")); return false;	}
	virtual bool IsInRange() {	UE_LOG(LogTemp, Error, TEXT("RequiresInRange: must be overriden")); return false;	}
	virtual bool IsDone() {	UE_LOG(LogTemp, Error, TEXT("IsActionDone: must be overriden")); return false;	}
	
	virtual FVector GetTargetLocation() { return Target->GetActorLocation(); }

	void AddPrecondition(FString key, bool value) { Preconditions.Add(key, value); }
    void RemovePrecondition(FString key) { Preconditions.Remove(key); }
    void AddEffect(FString key, bool value) { Effects.Add(key, value); }
    void RemoveEffect(FString key) { Effects.Remove(key); }
    
    TMap<FString, bool> GetPreconditions() { return Preconditions; }
    TMap<FString, bool> GetEffects() { return Effects; }
	

	void Reset();
};
