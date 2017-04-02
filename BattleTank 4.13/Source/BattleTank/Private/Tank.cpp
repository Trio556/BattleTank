// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Public/TankBarrel.h"
#include "Public/Projectile.h"
#include "Public/Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Fire()
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