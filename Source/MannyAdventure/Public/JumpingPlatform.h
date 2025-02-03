// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlatformBase.h"
#include "JumpingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class MANNYADVENTURE_API AJumpingPlatform : public APlatformBase
{
	GENERATED_BODY()

public:
	AJumpingPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpPlatform|Properties")
	float BounceStrength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpPlatform|Properties")
	bool bHitX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpPlatform|Properties")
	bool bHitY;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpPlatform|Properties")
	bool bHitZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpPlatform|Properties")
	float JumpPlatformCoolDown;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector Impulse, const FHitResult& Hit);
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ResetJumpPlatform();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxComponent;
	
private:
	float LastHitTime;
	float FallingSpeed;

	FTimerHandle JumpPlatformCoolDownTimer;
};
