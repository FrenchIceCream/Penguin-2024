// Fill out your copyright notice in the Description page of Project Settings.

#include "FootComp.h"
#include "MyCharacter.h"
#include "LegManager.h"


// Sets default values for this component's properties
UFootComp::UFootComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

	Planted = true;
	TimeSinceUnplanted = 0;
	RayLength = 20;
	StepDistance = 10;
	StepHeight = 30;
	HeightOffset = 1;
}

// Called when the game starts or when spawned
void UFootComp::BeginPlay()
{
	Super::BeginPlay();
	FootPosition = GetComponentLocation();

	StartPosition = FootPosition;
	LegManager = Cast<ULegManager>(GetOwner()->GetComponentByClass(ULegManager::StaticClass()));
	if (LegManager->SpeedCurve)
		SpeedCurve = LegManager->SpeedCurve;
	if (LegManager->HeightCurve)
		HeightCurve = LegManager->HeightCurve;
}

// Called every frame
void UFootComp::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//=============================//
void UFootComp::UpdateLeg()
{
	//UE_LOG(LogTemp, Warning, TEXT("CompLoc: %f;%f;%f"), GetRelativeLocation().X, GetRelativeLocation().Y, GetRelativeLocation().Z);
	TargetPosition = GetTargetLocation();
	DrawDebugPoint(GetWorld(), TargetPosition, 5, FColor::Magenta, false, StepTime, 1);
	Replant(TargetPosition);
}

FVector UFootComp::GetTargetLocation()
{
	FVector TracePosition = StartPosition;
	FVector RayStart = StartPosition;

	FVector ForwardVector = GetOwner()->GetActorForwardVector();
	FVector RayEnd = RayStart + ForwardVector*RayLength;
	
	//===DEBUG===
	//DrawDebugLine(GetWorld(), RayStart, RayEnd, FColor::Green, false, 1, 0, 1);
	
	//casting a ray to see if it hits something
	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	//DrawDebugLine(GetWorld(), RayStart, RayEnd, FColor::Magenta, false, 1, 0, 1);
	//DrawDebugLine(GetWorld(), RayEnd + FVector(0,0,1)*RayLength, RayEnd, FColor::Magenta, false, 1, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, RayEnd + FVector(0,0,1)*RayLength, RayEnd, TEnumAsByte<ECollisionChannel>(ECC_Camera), CollisionParams))
	{
		TracePosition = OutHit.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Hit something above: %s"), *OutHit.GetActor()->GetFullName());
	}
	else if (GetWorld()->LineTraceSingleByChannel(OutHit, RayStart, RayEnd, TEnumAsByte<ECollisionChannel>(ECC_Camera), CollisionParams))
	{
		TracePosition = OutHit.Location - ForwardVector*10;
		//UE_LOG(LogTemp, Warning, TEXT("Hit something in front of us: %s"), *OutHit.GetActor()->GetFullName());
	}
	else if (GetWorld()->LineTraceSingleByChannel(OutHit, RayEnd, RayEnd - FVector(0,0,2)*RayLength, TEnumAsByte<ECollisionChannel>(ECC_Camera), CollisionParams))
	{
		TracePosition = OutHit.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Hit something below: %s"), *OutHit.GetActor()->GetFullName());
	}
	return TracePosition + HeightOffset*FVector(0,0,1);
}

void UFootComp::Replant(const FVector& TargetPos)
{
	if (((TargetPos - FootPosition).Size() > StepDistance || !Planted) && LegManager->CanReplant(this))
	{
		if (Planted)
		{
			Planted = false;
			TimeSinceUnplanted = 0;
			//TODO
			//FootPosition = GetComponentLocation();
			StartPosition = FootPosition;
		}
		
		TakeStep(StartPosition, TargetPos);
	}
}

void UFootComp::TakeStep(const FVector& StartPos, const FVector& TargetPos)
{
	if (!Planted)
	{
		TimeSinceUnplanted = TimeSinceUnplanted + GetWorld()->GetDeltaSeconds();
		//how far we are in our step
		float PercentageReplanted = TimeSinceUnplanted/StepTime;
		float SpeedCurveValue = SpeedCurve->GetFloatValue(PercentageReplanted);
		FVector FootPosNoHeight = FMath::Lerp(StartPos, TargetPos, SpeedCurveValue);
		FootPosNoHeight.Z = 0;
		//DrawDebugBox(GetWorld(), FootPosNoHeight, FVector(5,5,5), FColor::Orange, false, 1, 0, 1);

		float HeightCurveValue = HeightCurve->GetFloatValue(PercentageReplanted);
		FVector FootPosHeight = FVector(0, 0, TargetPos.Z +  HeightCurveValue*StepHeight);
		//DrawDebugBox(GetWorld(), FootPosNoHeight + FootPosHeight, FVector(5,5,5), FColor::Yellow, false, 1, 0, 1);
		FootPosition = FootPosNoHeight + FootPosHeight;

		//SetWorldLocation(FootPosition); //CHANGED
		
		if (this->GetName().Compare(FString("LeftFootComp")))
			DrawDebugBox(GetWorld(), FootPosition, FVector(5,5,5), FColor::Yellow, false, 0.1, 0, 1);
		else
			DrawDebugBox(GetWorld(), FootPosition, FVector(5,5,5), FColor::Orange, false, 0.1, 0, 1);
		
		if (TimeSinceUnplanted >= StepTime)
		{
			Planted = true;
			FootPosition = TargetPos;
			StartPosition = FootPosition;
		}
	}
}

bool UFootComp::IsPlanted()
{
	return Planted;
}

FVector UFootComp::GetFootPosition()
{
	return FootPosition;
}

FVector UFootComp::GetTargetPosition()
{
	return TargetPosition;
}

FVector UFootComp::GetStartPosition()
{
	return StartPosition;
}

void UFootComp::SetStepTime(float Speed)
{
	StepTime = StepDistance/Speed;
	//было RayLength/Speed
}