// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformBase.h"

APlatformBase::APlatformBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(SceneComponent);
	
	MoveSpeed = FVector::ZeroVector;
	RotateSpeed = FRotator::ZeroRotator;
	MaxDistance = 0.f;
}

void APlatformBase::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

void APlatformBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MoveSpeed.IsZero())
	{
		MoveActor(DeltaTime);
	}
	if (!RotateSpeed.IsZero())
	{
		RotateActor(DeltaTime);
	}
}

void APlatformBase::MoveActor(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	
	CurrentLocation += MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);
	
	float Distance = FVector::Dist(StartLocation, CurrentLocation);
	
	if (Distance > MaxDistance)
	{
		// 법선구하기
		FVector Direction = MoveSpeed.GetSafeNormal();
		StartLocation += MaxDistance * Direction;
		SetActorLocation(StartLocation);
		
		MoveSpeed = -MoveSpeed;
	}
	
}

void APlatformBase::RotateActor(float DeltaTime)
{
	AddActorLocalRotation(RotateSpeed * DeltaTime);
}



