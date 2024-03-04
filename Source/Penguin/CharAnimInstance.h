// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharAnimInstance.generated.h"
/**
 * 
 */

class AMyCharacter;
class ULegManager;
class UFootComp;

UCLASS()
class PENGUIN_API UCharAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector LeftFootPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector RightFootPos;
/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator LeftFootRot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator RightFootRot;
*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AMyCharacter* Char;
private:

	ULegManager* LegManager;

	UFootComp* LeftFoot;
	UFootComp* RightFoot;

public:
	UCharAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
