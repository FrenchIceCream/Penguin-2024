
#include "GoapAgent.h"
#include "Action.h"
#include "GoalPlanner.h"
#include "../MyCharacter.h"
#include "FSM.h"
#include "IdleState.h"
#include "MoveState.h"
#include "PerformActionState.h"

// Sets default values for this component's properties
UGoapAgent::UGoapAgent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AvailableActions = TSet<UAction*>();
	CurrentActions = new TQueue<UAction*>();
	FSM = NewObject<UFSM>();
}

void UGoapAgent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FSM->StateTick(this, Planner, Agent);	
}

// Called when the game starts
void UGoapAgent::BeginPlay()
{
	Super::BeginPlay();

	Agent = Cast<AMyCharacter>(GetOwner());
	Planner = Agent->GoalPlanner;
	auto actions = Agent->GetActions();
	for (auto action : actions)
		AddAction(action);
}
