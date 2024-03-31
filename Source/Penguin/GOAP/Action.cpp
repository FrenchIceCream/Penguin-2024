// Fill out your copyright notice in the Description page of Project Settings.

#include "Action.h"
UAction::UAction()
{
	//PrimaryComponentTick.bCanEverTick = false;
    Preconditions = TMap<FString, bool>();
    Effects = TMap<FString, bool>();
}
