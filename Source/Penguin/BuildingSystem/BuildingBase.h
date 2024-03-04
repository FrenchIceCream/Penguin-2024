// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingDataAsset.h"
#include "BuildingBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class PENGUIN_API ABuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildingBase();
	virtual void Tick(float DeltaTime) override;
	void SetData(UBuildingDataAsset * BuildingDataAsset);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UBuildingDataAsset * BuildingData;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * StaticMeshComp;
};
