// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

class UInputMappingContext;
class UInputAction;
class UBuildingModeComponent;

UCLASS()
class PENGUIN_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera")
	float MoveSpeed = 300.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera")
	float ZoomStep = 50.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera")
	float MinZoom = 300.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera")
	float MaxZoom = 2500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera")
	float RotateSpeed = 10.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Camera")
	float CameraAngle = -40.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UBuildingModeComponent * BuildingModeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext * DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext * BuildModeMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction * MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction * RotateAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction * RotateKeyboardAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction * ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction * BuildDeployAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction * BuildCancelAction;


	void Move(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
	void RotateWithKeys(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);

	void BuildDeploy(const FInputActionValue& Value);
	void BuildCancel(const FInputActionValue& Value);

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* SpringArmComp;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* CameraComp;

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	FRotator TargetRotation;
};
