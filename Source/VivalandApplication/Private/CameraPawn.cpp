// Fill out your copyright notice in the Description page of Project Settings.



#include "CameraPawn.h"
#include "AIController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TankPlayerController.h"
#include "TankProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tasks/AITask_MoveTo.h"
#include "Tasks/GameplayTask_WaitDelay.h"


// Sets default values
ACameraPawn::ACameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		const FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld,
		                                                         EAttachmentRule::KeepRelative,
		                                                         EAttachmentRule::KeepRelative, false);
		SpawnedTank = SpawnTank();
		TankAIController = Cast<AAIController>(SpawnedTank->GetController());
		AttachToActor(SpawnedTank, AttachmentTransformRules);
	}
}


// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Get the player controller
	PC = Cast<ATankPlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PC->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions
	PEI->BindAction(InputMove, ETriggerEvent::Triggered, this, &ACameraPawn::Move);
	PEI->BindAction(InputShoot, ETriggerEvent::Triggered, this, &ACameraPawn::Shoot);
}

void ACameraPawn::Move(const FInputActionValue& Value)
{
	FHitResult OutHit;
	PC->GetHitResultUnderCursor(ECC_WorldStatic,false,OutHit);
	MoveServer(OutHit.ImpactPoint);
}

void ACameraPawn::MoveServer_Implementation(const FVector& HitLocation)
{
	if(!bIsMoving)
	{
		if (UAITask_MoveTo* MoveTo = UAITask_MoveTo::AIMoveTo(TankAIController, HitLocation,nullptr,1, EAIOptionFlag::Disable))
		{
			bIsMoving = true;
			MoveTo->OnMoveFinished.AddDynamic(this, &ACameraPawn::OnMoveTaskFinished);
			MoveTo->ReadyForActivation();

			FVector OriginVector = SpawnedTank->GetActorLocation();
			OriginVector.Z = 0;
			SpawnedTank->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(OriginVector,HitLocation));
		}
	}
}

void ACameraPawn::OnMoveTaskFinished(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController)
{
	bIsMoving = false;
}

void ACameraPawn::Shoot(const FInputActionValue& Value)
{
	ShootServer();
}

void ACameraPawn::ShootServer_Implementation()
{
	if(bCanShoot)
	{
	bCanShoot = false;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	SpawnParameters.Owner = SpawnedTank;
	GetWorld()->SpawnActor<ATankProjectile>(GetActorLocation(),SpawnedTank->GetActorRotation(),SpawnParameters);
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACameraPawn::OnShotCooldownFinished, TankShotCooldown, false);
	}
}

void ACameraPawn::OnShotCooldownFinished_Implementation()
{
	bCanShoot = true;
}


