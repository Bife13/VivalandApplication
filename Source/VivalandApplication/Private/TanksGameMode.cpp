// Fill out your copyright notice in the Description page of Project Settings.


#include "VivalandApplication/Public/TanksGameMode.h"

#include "EngineUtils.h"
#include "Engine/PlayerStartPIE.h"
#include "GameFramework/PlayerStart.h"

AActor* ATanksGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	UWorld* World = GetWorld();
	TArray<APlayerStart*> StartPoints;
	
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* Start = *It;
		StartPoints.Add(Start);
	}

	if(StartPoints[JoinedPlayers])
	{
		const int Index = JoinedPlayers;
		JoinedPlayers++;
		return StartPoints[Index];
	}
	
	return StartPoints[FMath::RandRange(0,StartPoints.Num()-1)];
}
