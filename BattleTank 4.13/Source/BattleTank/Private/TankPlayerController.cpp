// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Public/TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *ControlledTank->GetName());
	}	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation; //Out Parameter

	if (GetSightRayHitLocation(HitLocation)) // Is going to Line Trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

		//TODO Tell controlled tank to aim at this point
	}
}

//Line Traces to a hit location, returns true when hit's landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//RayCast from crosshair location
	//Get Location of where the raycast hits 
		//if there is no location return false
		//else assign location to HitLocation
		// return true

	HitLocation = FVector(1.0);

	return true;
}