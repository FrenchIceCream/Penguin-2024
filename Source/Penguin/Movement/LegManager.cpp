// Fill out your copyright notice in the Description page of Project Settings.

#include "LegManager.h"
#include "../MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "FootComp.h"


// Sets default values for this component's properties
ULegManager::ULegManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULegManager::BeginPlay()
{
	Super::BeginPlay();
	Char = Cast<AMyCharacter>(GetOwner());
	Char->GetComponents<UFootComp>(Legs);
	if (!SpeedCurve)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO SPEED CURVE SELECTED"));
	}
	if (!HeightCurve)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO HEIGHT CURVE SELECTED"));
	}
	HalfHeight = ((Char->GetActorLocation() - Char->GetMesh()->GetComponentLocation()) * Char->GetActorUpVector()).Size();
}


// Called every frame
void ULegManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//TODO ShouldPlant???
	if ((Char->GetMovementComponent()->Velocity.Length()> 0  || ShouldPlant()) && HeightCurve && SpeedCurve)
		UpdateLegs();
	
	FVector LeftWorldPos = Legs[0]->GetFootPosition();
	FVector RightWorldPos = Legs[1]->GetFootPosition();
	float SurfaceOffset = LeftWorldPos.Z <= RightWorldPos.Z ? LeftWorldPos.Z : RightWorldPos.Z;
	float SurfaceOffsetTarget = LeftWorldPos.Z > RightWorldPos.Z ? LeftWorldPos.Z : RightWorldPos.Z;
	FVector RootLocation = UKismetMathLibrary::GetVectorArrayAverage(TArray<FVector>{LeftWorldPos, RightWorldPos});

	//TODO Height on incline
	Char->SetActorLocation(RootLocation*FVector(1,1,0) + FVector(0,0,HalfHeight + FMath::Lerp(SurfaceOffset, SurfaceOffsetTarget, 1 - (SurfaceOffsetTarget - SurfaceOffset)/SurfaceOffsetTarget)));
}

void ULegManager::UpdateLegs()
{
	for(UFootComp* Foot: Legs)
	{
		Foot->UpdateLeg();
	}
}

bool ULegManager::CanReplant(UFootComp* Foot)
{
	for(UFootComp* FootOther: Legs)
	{
		if (Foot != FootOther && FootOther->IsPlanted())
			return true;
	}
	return false;
}

bool ULegManager::ShouldPlant()
{
	for(UFootComp* Foot: Legs)
	{
		if (!Foot->IsPlanted())
			return true;
	}
	return false;
}