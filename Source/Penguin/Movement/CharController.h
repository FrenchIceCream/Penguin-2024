// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharController.generated.h"

class UAction;
UCLASS()
class PENGUIN_API ACharController : public AAIController
{
	GENERATED_BODY()
	
public:
	bool MoveToTarget(APawn *Agent, UAction *Action);
	
	void CheckIfAIWorks();
};
