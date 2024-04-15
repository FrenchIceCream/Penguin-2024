// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"

#include "MyCharacter.generated.h"

class ULegManager;
class UFootComp;
class UCharAnimInstance;
class UCameraComponent;
class USpringArmComponent;
class UAction;
class UGoalPlanner;
class ACharController;
class UGoapAgent;
class UWidgetComponent;
//class UThoughtBubble;

UCLASS()
class PENGUIN_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	void DecreaseHunger();
	void IncreaseHunger();
	void Die();
	void DestroyChar();
	void AddActions();

	FTimerHandle HungerTimerHandle;

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI") 
    	UGoalPlanner* GoalPlanner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI") 
    	UGoapAgent* GoapAgent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		ULegManager* LegManager;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		UFootComp* LeftFoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		UFootComp* RightFoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Animation Sockets")
		FName LeftSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Animation Sockets")
		FName RightSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Character Speed")
	float WalkingSpeed = 30;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation|Character Speed")
	float SprintSpeed = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GOAP|Actions")
	TArray<TSubclassOf<UAction>> ActionsToAdd;
	// UPROPERTY()
	// UThoughtBubble* BubbleWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GOAP")
	bool Testing = false;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	TSet<UAction*> GetActions() {return Actions;}

	virtual TMap<FString, bool> GetWorldState();
	virtual TMap<FString, bool> GetGoal();

	bool MoveToTarget(UAction* Action);

	int GetHunger() {return Hunger;};
	void SatisfyHunger(int Amount) {Hunger += Amount;};
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UCharAnimInstance* AnimInst;

	UPROPERTY()
	TSet<UAction*> Actions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Hunger = 100;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* StatsBarWidgetComp;

	UPROPERTY()
	ACharController* PlayerAI;
};
