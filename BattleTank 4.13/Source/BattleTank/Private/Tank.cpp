// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/Projectile.h"
#include "Public/Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	// No need to protect points as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurrentReference(UTankTurrent* TurrentToSet)
{
	TankAimingComponent->SetTurrentReference(TurrentToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!Barrel) return;

	//Spawn Projectile at barrels projectile socket
	auto ProjectileSocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto ProjectileSocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
	FActorSpawnParameters ProjectileSpawnParams;

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileSocketLocation, ProjectileSocketRotation, ProjectileSpawnParams);

	Projectile->LaunchProjectile(LaunchSpeed);
}