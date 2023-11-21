// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "InputAction.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class VIVALANDAPPLICATION_API ACameraPawn : public APawn, public IGameplayTaskOwnerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	ATank* SpawnTank();
	
	UFUNCTION()
	void OnMoveTaskFinished(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController);
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMove;
 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputShoot;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(BlueprintReadWrite)
	ATank* SpawnedTank;

	UPROPERTY()
	AAIController* TankAIController;

	UPROPERTY()
	ATankPlayerController* PC;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION(Server,Reliable)
	void MoveServer(const FVector& HitLocation);

	UFUNCTION()
	void Shoot(const FInputActionValue& Value);

	UFUNCTION(Server,Reliable)
	void ShootServer();
	
	UFUNCTION(Server,Reliable)
	void OnShotCooldownFinished();

	UPROPERTY()
	bool bIsMoving = false;
	
	UPROPERTY()
	bool bCanShoot = true;

	UPROPERTY(EditAnywhere)
	float TankShotCooldown = 5;

};
