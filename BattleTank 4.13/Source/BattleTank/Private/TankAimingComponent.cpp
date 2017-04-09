// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Public/Projectile.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurrent.h"
#include "Public/TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; 
	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet)
{
	Barrel = BarrelToSet;
	Turrent = TurrentToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHasAimSolution =
		UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

	//Calculate the out launch velocity
	if (bHasAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turrent)) { return; }

	//Work-out Difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turrent->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded && ensure(Barrel))
	{
		//Spawn Projectile at barrels projectile socket
		auto ProjectileSocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto ProjectileSocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
		FActorSpawnParameters ProjectileSpawnParams;

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileSocketLocation, ProjectileSocketRotation, ProjectileSpawnParams);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}