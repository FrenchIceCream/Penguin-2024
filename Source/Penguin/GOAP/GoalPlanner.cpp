
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

	//TODO вот тут скорее всего будет subclass
	Actions = Cast<AMyCharacter>(GetOwner())->GetActions();
}


// Called every frame
void UGoalPlanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}