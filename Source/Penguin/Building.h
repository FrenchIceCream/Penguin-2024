// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "BuildingType.h"
#include "Building.generated.h"

UCLASS()
class PENGUIN_API ABuilding : public AActor
{
	GENERATED_BODY()

public:	
	ABuilding();	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EntrancePos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent * Entrance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuildingType BuildingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent * StaticMeshComp;
protected:
	virtual void BeginPlay() override;
};
