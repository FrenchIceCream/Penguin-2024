// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoalPlanner.generated.h"

class UAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUIN_API UGoalPlanner : public UActorComponent
{
	GENERATED_BODY()
	TSet<UAction*> Actions;

	TQueue<UAction*> ActionSequence;
public:	
	// Sets default values for this component's properties
	UGoalPlanner();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FindBestPath(FString GoalAction);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
