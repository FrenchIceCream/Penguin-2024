// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicResourceManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUIN_API UBasicResourceManager : public UActorComponent
{
	GENERATED_BODY()

	int ResourceCount;

	int MinResourceCount = 0;
	int MaxResourceCount = 10;
public:	
	UBasicResourceManager();

	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMinResource(int min) { MinResourceCount = min; }
	void SetMaxResource(int max) { MaxResourceCount = max; }
	void SetResourceCount(int count) {ResourceCount = count; }

	int GetResourceCount() { return ResourceCount; }

	void AddResource(int count) { ResourceCount += count; }
	void AddResource() { ResourceCount ++; }

protected:
	virtual void BeginPlay() override;
	
};
