// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward Declaration
class UTankBarrel;
class UTankTurrent;

//Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet);

	void AimAt(FVector HitLocation);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringStatus = EFiringState::Locked;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4500; //Starting Value of 1000 m/s

	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;

	UTankTurrent* Turrent = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
