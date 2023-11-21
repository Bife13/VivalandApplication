// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TankProjectile.generated.h"

UCLASS()
class VIVALANDAPPLICATION_API ATankProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATankProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(Server, Reliable)
	void HitServer(AActor* OtherActor);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditInstanceOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	float Lifetime;
	
	UPROPERTY()
	float MaximumLifetime = 2;
	
};
