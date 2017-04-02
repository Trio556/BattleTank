// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(PlayerTank && ControlledTank))
	{
		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		//Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		//Fire if Ready
		//ControlledTank->Fire();// TODO: limit firing rate
	}
}