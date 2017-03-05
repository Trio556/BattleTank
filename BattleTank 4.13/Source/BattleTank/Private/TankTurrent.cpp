// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Public/TankTurrent.h"

void UTankTurrent::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Rotation Change: %f | RawNewRotation: %f"), RotationChange, NewRotation);
}
