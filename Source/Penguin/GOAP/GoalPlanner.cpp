
#include "GoalPlanner.h"
#include "Action.h"
#include "../MyCharacter.h"

// Sets default values for this component's properties
UGoalPlanner::UGoalPlanner()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UGoalPlanner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UGoalPlanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


bool UGoalPlanner::BuildGraph(FGoapNode* parent, TArray<FGoapNode*>& leaves, TSet<UAction *> usableActions, TMap<FString, bool> goal)
{
	bool found = false;

	for (UAction* Action : usableActions)
	{
		if (InState(Action->GetPreconditions(), parent->State))
		{
			TMap<FString, bool> currentState = PopulateState(parent->State, Action->GetEffects());
			FGoapNode* node = new FGoapNode(parent, parent->Cost + Action->ActionCost, currentState, Action);
			if (InState(goal, currentState))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Added leaves"));
				leaves.Add(node);
				found = true;
			}
			else
			{
				TSet<UAction*> subset = GetActionSubset(usableActions, Action);
				bool found_sub = BuildGraph(node, leaves, subset, goal);
				if (found_sub)
					found = true;
			}
		}
	}

    return found;
}

bool UGoalPlanner::InState(TMap<FString, bool> test, TMap<FString, bool> state)
{
	bool allMatch = true;
	for (auto pair : test)
	{
		bool match = false;
		for (auto pair2 : state)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Your message: %s, %s, %d, %d"), *pair.Key, *pair2.Key, pair.Value, pair2.Value);
			if (pair.Key == pair2.Key && pair.Value == pair2.Value)
			{
				match = true;
				break;
			}
		}
		if (!match)
		{
			allMatch = false;
			break;
		}
	}

    return allMatch;
}

TMap<FString, bool> UGoalPlanner::PopulateState(TMap<FString, bool> currentState, TMap<FString, bool> stateChange)
{
	TMap<FString, bool> state = TMap<FString, bool>();
	for (auto pair : currentState)
		state.Add(pair.Key, pair.Value);

	for (auto pair : stateChange)
	{
		bool exists = false;
		
		for (auto pair2 : state)
		{
			if (pair.Key == pair2.Key)
			{
				exists = true;
				break;
			}
		}

		if (exists)
			state.Remove(pair.Key);
			
		state.Add(pair.Key, pair.Value);
	}
	return state;
}

TSet<UAction *> UGoalPlanner::GetActionSubset(TSet<UAction *> actions, UAction *actionToRemove)
{
	TSet<UAction *> Subset = TSet<UAction *>();
	for (UAction* Action : actions)
		if (Action != actionToRemove)
			Subset.Add(Action);
    
	return Subset;
}

TArray<UAction *> UGoalPlanner::FindBestPath(AMyCharacter *Agent, TSet<UAction *> AvailableActions, TMap<FString, bool> WorldState, TMap<FString, bool> Goal)
{
	for (UAction *Action : AvailableActions)
		Action->Reset();

	TSet<UAction*> UsableActions = TSet<UAction*>();

	for (UAction* Action : AvailableActions)
	{
		if (Action->CheckProceduralPrecondition(Agent))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Procedural Precondition met: %s"), *Action->GetName());
			UsableActions.Add(Action);
		}
	}

	TArray<FGoapNode*> Nodes = TArray<FGoapNode*>();
	FGoapNode* StartNode = new FGoapNode(nullptr, 0, WorldState, nullptr);

	if (!BuildGraph(StartNode, Nodes, UsableActions, Goal))
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find a GOAP path!"));
		return TArray<UAction *>();
	}

	//UE_LOG(LogTemp, Warning, TEXT("Nodes: %d"), Nodes.Num());
	FGoapNode* BestNode = nullptr;
	for (FGoapNode* Node : Nodes)
	{
		if (!BestNode || Node->Cost < BestNode->Cost)
			BestNode = Node;
	}

	TArray<UAction*> res = TArray<UAction*>();
	FGoapNode* node = BestNode;
	while (node)
	{
		if (node->Action)
			res.Insert(node->Action, 0);
		node = node->Parent;
	}


	//UE_LOG(LogTemp, Warning, TEXT("res: %d"), res.Num());
    return res;
}
