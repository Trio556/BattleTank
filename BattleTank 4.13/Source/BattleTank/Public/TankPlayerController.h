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

	ATank* GetControlledTank() const;

	//Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
private:

	//Get's the Hit Location of where the cross hair is and returns true when there is a hit
	bool GetSightRayHitLocation(FVector& HitLocation) const;

};
