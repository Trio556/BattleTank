// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward Declaration
class UTankTurrent;
class UTankTrack;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Action")
		void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	//Todo remove once firing is refactored
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4500; //Starting Value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	//Tracks that the tank will use
	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;

	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;
};
