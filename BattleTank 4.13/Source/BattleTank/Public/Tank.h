// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward Declaration
class UTankAimingComponent;
class UTankTurrent;
class UTankTrack;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurrentReference(UTankTurrent* TurrentToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetRightTrackReference(UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetLeftTrackReference(UTankTrack* LeftTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Action)
		void Fire();

protected:

	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4500; //Starting Value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	//Tracks that the tank will use
	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;


	//Barrel reference for Projectile
	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;
};
