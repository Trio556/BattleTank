// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Public/Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	TankProjectile->bAutoActivate = 0;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile::LaunchProjectile(float Speed)
{
	UE_LOG(LogTemp, Warning, TEXT("Speed %f"), Speed);
	
	TankProjectile->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);

	TankProjectile->Activate(true);
}