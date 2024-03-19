// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoalPlanner.generated.h"

class UAction;
class AMyCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUIN_API UGoalPlanner : public UActorComponent
{
	GENERATED_BODY()
	TSet<UAction*> Actions;

	//TQueue<UAction*>* ActionSequence;

	bool BuildGraph(FGoapNode* parent, TArray<FGoapNode*> leaves, TSet<UAction*> usableActions, TMap<FString, bool> goal);
	bool InState(TMap<FString, bool> test, TMap<FString, bool> state);
	TMap<FString, bool> PopulateState(TMap<FString, bool> currentState, TMap<FString, bool> stateChange);
	TSet<UAction*> GetActionSubset(TSet<UAction*> actions, UAction* actionToRemove);
public:	
	// Sets default values for this component's properties
	UGoalPlanner();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TQueue<UAction*>* FindBestPath(AMyCharacter* Agent, TSet<UAction*> AvailableActions, TMap<FString, bool> WorldState, TMap<FString, bool> Goal);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};

USTRUCT()
struct FGoapNode
{
    GENERATED_BODY()

	FGoapNode* Parent;
	float Cost;
	TMap<FString, bool> State;
	UAction* Action;

	FGoapNode() 
	{
		Parent = nullptr;
		Cost = -1;
		State = TMap<FString, bool>();
		Action = nullptr;
	}

	FGoapNode(FGoapNode* parent, float runningCost, TMap<FString, bool> state, UAction* action) 
	{
		Parent = parent;
		Cost = runningCost;
		State = state;
		Action = action;
	}
};

template<>
struct TStructOpsTypeTraits< TQueue<UAction*> > : public TStructOpsTypeTraitsBase2< TQueue<UAction*> >
{
   enum
   {
      WithCopy = false
   };
};
