// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoapAgent.generated.h"

class AMyCharacter;
class UGoalPlanner;
class UAction;
class UFSM;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUIN_API UGoapAgent : public UActorComponent
{
	GENERATED_BODY()

	TSet<UAction*> AvailableActions;
	TQueue<UAction *>* CurrentActions;
	AMyCharacter* Agent;
	UGoalPlanner* Planner;
	UFSM* FSM;

	bool HasActionPlan() {return !CurrentActions->IsEmpty();}
public:	
	// Sets default values for this component's properties
	UGoapAgent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddAction(UAction* Action) {AvailableActions.Add(Action);}
	void RemoveAction(UAction* Action) {AvailableActions.Remove(Action);}

	TSet<UAction*> GetAvailableActions() {return AvailableActions;}
	TQueue<UAction *>* GetCurrentActions() {return CurrentActions;}
	void SetCurrentActions(TQueue<UAction *>* actions) {CurrentActions = actions;}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;		
};