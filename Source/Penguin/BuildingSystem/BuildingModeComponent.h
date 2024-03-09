// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Building.h"
#include "Engine/AssetManager.h"
#include "BuildingModeComponent.generated.h"


class APlayerControl;
class APlayerPawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildModeEnterDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENGUIN_API UBuildingModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildingModeComponent();

	static UBuildingModeComponent* FindBuildingModeComponent(const AActor* Actor) 
	{ return (Actor ? Actor->FindComponentByClass<UBuildingModeComponent>() : nullptr); };

	FOnBuildModeEnterDelegate OnBuildModeEnterEvent;

	void LoadBuildingData();
	void EnterBuildMode();
	void ExitBuildMode();
	void EnterBuildPlacementMode(UBuildingDataAsset* BuildingDataAsset);

	TArray<FPrimaryAssetId> GetBuildingData() const {return BuildingItemsData; };

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;
	void UpdatePlacementStatus();

	UFUNCTION()
	void OnBuildingDataLoaded(TArray<FPrimaryAssetId> BuildingAssetsIds);

	UFUNCTION()
	void PlaceBuilding(UBuildingDataAsset* BuildingDataAsset, const FTransform& Position);
	void PlaceBuildingInWorld(UBuildingDataAsset* BuildingDataAsset, const FTransform& Position);

	UFUNCTION()
	void OnBuildComplete(const EBuildState NewBuildingState);

	UPROPERTY()
	UAssetManager* AssetManager;

	UPROPERTY()
	TArray<FPrimaryAssetId> BuildingItemsData;

	UPROPERTY()
	APlayerControl* PlayerController;

	UPROPERTY()
	UWorld* World;

	UPROPERTY()
	ABuilding* CurrentBuilding;

	UPROPERTY()
	APlayerPawn* PlayerPawn;

	UPROPERTY()
	bool IsPlacable = false;
};
