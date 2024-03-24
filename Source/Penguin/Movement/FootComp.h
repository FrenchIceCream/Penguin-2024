// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FootComp.generated.h"

//class AMyCharacter;
class ULegManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUIN_API UFootComp : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFootComp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UCurveFloat* SpeedCurve;

	UCurveFloat* HeightCurve;

	bool Planted;

	float TimeSinceUnplanted;

	float RayLength;

	float StepDistance;

	float StepTime;

	float StepHeight;

	float HeightOffset;

	FVector FootPosition;

	FVector StartPosition;

	FVector TargetPosition;

//	FRotator FootRotation;

	FVector GetTargetLocation();

	void Replant(const FVector& TargetPos);

	void TakeStep(const FVector& StartPos, const FVector& TargetPos);

	ULegManager* LegManager;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	void UpdateLeg();

	bool IsPlanted();

	FVector GetFootPosition();

	FVector GetTargetPosition();

	FVector GetStartPosition();

//	FRotator GetFootRotation();

	void SetStepTime(float Speed);
};
