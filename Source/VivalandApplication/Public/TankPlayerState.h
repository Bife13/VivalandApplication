// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TankPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class VIVALANDAPPLICATION_API ATankPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void IncreasePlayerScore();
	
	UFUNCTION(BlueprintCallable)
	int GetPlayerScore() const;

protected:

	UPROPERTY(Replicated)
	int PlayerScore;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
};
