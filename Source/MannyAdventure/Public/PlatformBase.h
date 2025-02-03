// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformBase.generated.h"

UCLASS()
class MANNYADVENTURE_API APlatformBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APlatformBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;

public:
	// 이동
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	FVector MoveSpeed;
	// 회전
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	FRotator RotateSpeed;
	// 최대이동거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
	float MaxDistance;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// 액터 이동
	UFUNCTION(BlueprintCallable)
	virtual void MoveActor(float DeltaTime);
	// 액터 회전
	UFUNCTION(BlueprintCallable)
	virtual void RotateActor(float DeltaTime);
	
	// 초기 위치
	FVector StartLocation;
};
