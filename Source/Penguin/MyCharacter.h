// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"
#include "FootComp.h" 
#include "LegManager.h" 
#include "CharAnimInstance.h"

#include "MyCharacter.generated.h"

UCLASS()
class PENGUIN_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ULegManager* LegManager;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UFootComp* LeftFoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UFootComp* RightFoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sockets")
		FName LeftSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sockets")
		FName RightSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Speed")
	float WalkingSpeed = 30;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Speed")
	float SprintSpeed = 50;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Action mappings + axis mappings
	// void MoveForward(float AxisVal);
	// void MoveRight(float AxisVal);
	// void SprintStart();
	// void SprintEnd();

	UCharAnimInstance* AnimInst;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
