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

	ATank* GetControlledTank() const;

	//Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	//Get's the Hit Location of where the cross hair is and returns true when there is a hit
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
};
