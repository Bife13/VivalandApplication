// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VIVALANDAPPLICATION_API ATanksGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

protected:
	
	UPROPERTY()
	int JoinedPlayers = 0;

};
