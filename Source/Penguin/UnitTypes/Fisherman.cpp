// Fill out your copyright notice in the Description page of Project Settings.

#include "Fisherman.h"
#include "../UI/ThoughtBubble.h"
#include "Components/WidgetComponent.h"

TMap<FString, bool> AFisherman::GetWorldState()
{
    TMap<FString, bool> res = TMap<FString, bool>();
	res.Add("NeedsFish", FishCount < 5);

    if (Testing)
		res.Add("Testing", true);

    return res;
}

TMap<FString, bool> AFisherman::GetGoal()
{
    TMap<FString, bool> res = TMap<FString, bool>();

	if (Testing)
		res.Add("DoneTesting", true);
	else if (Hunger < 20)
	{
		//UE_LOG(LogTemp, Error, TEXT("Inside GetGoal"));
		res.Add("GetFood", true);
	}
    else if (FishCount == 5)
	{
		res.Add("BringFishToBuilding", true);
	}
	else
	{
		res.Add("HasFish", true);
	}
    

    return res;
}
