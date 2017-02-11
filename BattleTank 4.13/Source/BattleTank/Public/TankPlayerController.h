// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be included at the end

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	//Relative position of the crosshair in the X plane
	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

	//Relative position of the crosshair in the Y Plane
	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	ATank* GetControlledTank() const;

	//Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	//Get's the Hit Location of where the cross hair is and returns true when there is a hit
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	//Gets the current Look Direction from the Cross Hair's screen location
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	//Get's a hit location of where you are looking
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
