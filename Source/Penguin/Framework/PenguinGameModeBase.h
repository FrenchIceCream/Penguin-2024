// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PenguinGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PENGUIN_API APenguinGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	APenguinGameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
