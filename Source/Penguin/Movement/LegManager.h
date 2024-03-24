// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "LegManager.generated.h"

class AMyCharacter;
class UFootComp;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUIN_API ULegManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULegManager();

	TArray<UFootComp*> Legs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* SpeedCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* HeightCurve;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CanReplant(UFootComp* Foot);

private:
	AMyCharacter* Char;

	float HalfHeight;

	void UpdateLegs();
	bool ShouldPlant();
};
