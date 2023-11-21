// Fill out your copyright notice in the Description page of Project Settings.


#include "TankProjectile.h"

#include "CameraPawn.h"
#include "TankPlayerState.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ATankProjectile::ATankProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	MeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
	MeshComponent->SetRelativeScale3D(FVector(.5f,.5f,.5f));
	MeshComponent->SetCollisionProfileName("OverlapAll");
	

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovementComponent->MaxSpeed = 2000;
	ProjectileMovementComponent->InitialSpeed = 1000;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	
}

// Called when the game starts or when spawned
void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	SetReplicateMovement(true);
	MeshComponent->SetIsReplicated(true);
	
}

void ATankProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(OtherActor != Owner)
	{
		if(HasAuthority())
		{
			const ACameraPawn* CameraPawn = Cast<ACameraPawn>(this->GetInstigator());
			ATankPlayerState* PlayerState = Cast<ATankPlayerState>(CameraPawn->GetPlayerState());
			PlayerState->IncreasePlayerScore();	
			HitServer(OtherActor);
		}
	}
	Super::NotifyActorBeginOverlap(OtherActor);
}

void ATankProjectile::HitServer_Implementation(AActor* OtherActor)
{
	FVector Direction = UKismetMathLibrary::RandomUnitVector();
	Direction.Z = 0;
	OtherActor->SetActorLocation(OtherActor->GetActorLocation() + Direction * 1200);
	Destroy();
}

// Called every frame
void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Lifetime += DeltaTime;
	if(Lifetime >= MaximumLifetime)
	{
		Destroy();
	}
}

