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

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet)
{
	Barrel = BarrelToSet;
	Turrent = TurrentToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringState::Reloading;
	}
	else if (RoundsLeft <= 0)
	{
		FiringStatus = EFiringState::OutOfAmmo;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringState::Aiming;
	}
	else
	{
		FiringStatus = EFiringState::Locked;
	}
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Barrel && Turrent)) { return; }

	//Work-out Difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	auto DeltaYaw = DeltaRotator.Yaw;

	if (DeltaYaw > 180 || DeltaYaw < -180) //Lecture Code (I like mine better): FMath::Abs(DeltaRotator.Yaw)
	{
		DeltaYaw *= -1; //Turrent->Rotate(DeltaRotator.Yaw)
	}
	//else Turrent->Rotate(-DeltaRotator.Yaw):End Lecture Code

	Turrent->Rotate(DeltaYaw);
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus == EFiringState::Aiming || FiringStatus == EFiringState::Locked)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		//Spawn Projectile at barrels projectile socket
		auto ProjectileSocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto ProjectileSocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
		FActorSpawnParameters ProjectileSpawnParams;

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileSocketLocation, ProjectileSocketRotation, ProjectileSpawnParams);

		Projectile->LaunchProjectile(LaunchSpeed);
		--RoundsLeft;

		LastFireTime = FPlatformTime::Seconds();
	}
}