// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetMeshComponent()->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (MeshAsset.Succeeded())
	{
		GetMeshComponent()->SetStaticMesh(MeshAsset.Object);
	}
	GetMeshComponent()->SetRelativeScale3D(FVector(1,.8f,.3f));
	GetMeshComponent()->SetCollisionProfileName("Pawn");
	GetMeshComponent()->SetCollisionObjectType(ECC_WorldDynamic);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


