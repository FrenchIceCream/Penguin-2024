// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/AssetManager.h"
#include "BuildingModeComponent.generated.h"


class APlayerControl;

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

	TArray<FPrimaryAssetId> GetBuildingData() const {return BuildingItemsData; };

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBuildingDataLoaded(TArray<FPrimaryAssetId> BuildingAssetsIds);

	UPROPERTY()
	UAssetManager* AssetManager;

	UPROPERTY()
	TArray<FPrimaryAssetId> BuildingItemsData;

	UPROPERTY()
	APlayerControl* PlayerController;
};
