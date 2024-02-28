// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GenericButtonWidget.h"
#include "PlayerControl.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class PENGUIN_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * StaticMeshComp;

public:	
	// Sets default values for this actor's properties
	ASpawnPoint();	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EntrancePos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AActor> ActorToSpawn;

	UPROPERTY()
	UGenericButtonWidget * ButtonWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Button")
	TSubclassOf<UUserWidget> ButtonWidgetClass;

	UFUNCTION(BlueprintCallable)
	void ToggleSpawnWidget(UPrimitiveComponent* Target, FKey ButtonPressed);

	UFUNCTION()
	void SpawnActor();

	UPROPERTY(BlueprintReadWrite)
	bool IsButtonVisible = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerControl* PlayerController;
};
