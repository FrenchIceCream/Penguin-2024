// Fill out your copyright notice in the Description page of Project Settings.

#include "Fisherman.h"

TMap<FString, bool> AFisherman::GetWorldState()
{
    TMap<FString, bool> res = TMap<FString, bool>();
	res.Add("HasFish", FishCount > 0);

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
        res.Add("GetFood", true);
    else if (FishCount == 0)
        res.Add("CatchFish", true);
    

    return res;
}
