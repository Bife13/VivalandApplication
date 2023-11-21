// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerState.h"

#include "Net/UnrealNetwork.h"

void ATankPlayerState::IncreasePlayerScore()
{
	PlayerScore+= 1;
}

int ATankPlayerState::GetPlayerScore() const
{
	return PlayerScore;
}

void ATankPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATankPlayerState, PlayerScore);
}
