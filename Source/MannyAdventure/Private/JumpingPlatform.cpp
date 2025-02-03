// Copyright Epic Games, Inc. All Rights Reserved.

#include "JumpingPlatform.h"
#include "MannyAdventure/MannyAdventureCharacter.h"
#include "Components/BoxComponent.h"

AJumpingPlatform::AJumpingPlatform()
{
	// 충돌감지 true
	StaticMeshComponent->SetNotifyRigidBodyCollision(true);
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AJumpingPlatform::OnHit);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(SceneComponent);
	BoxComponent->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	BoxComponent->SetCollisionResponseToChannels(ECR_Overlap);
	
	BounceStrength = 0.f;
	FallingSpeed = 0.f;
	JumpPlatformCoolDown = 3.f;
	bHitX = false;
	bHitY = false;
	bHitZ = false;
}

void AJumpingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AJumpingPlatform::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AJumpingPlatform::OnOverlapEnd);
}

void AJumpingPlatform::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector Impulse, const FHitResult& Hit)
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastHitTime < JumpPlatformCoolDown || FallingSpeed == 0.f)
	{
		return;
	}
	LastHitTime = CurrentTime;
	GetWorld()->GetTimerManager().SetTimer(JumpPlatformCoolDownTimer, this, &AJumpingPlatform::ResetJumpPlatform, JumpPlatformCoolDown, false);
	
	AMannyAdventureCharacter* Character = Cast<AMannyAdventureCharacter>(OtherActor);
	if (Character)
	{
		// 충돌 법선 벡터 방향 정규화값 저장
		FVector HitVector = Hit.Normal.GetSafeNormal();
		// 프로퍼티 설정값에 따른 팅김 여부 설정
		HitVector = FVector(bHitX ? HitVector.X : 0, bHitY ? HitVector.Y : 0, bHitZ ? HitVector.Z : 0);
		// 팅겨나가기 전 캐릭터의 속도 저장
		FVector BeforeHitVelocity = Character->GetVelocity();
		// 캐릭터가 충돌할때 법선벡터값이 음수로나와서 -곱해줌
		// 캐릭터가 높은곳에서 떨어질수록 더 높이 갈 수 있도록 낙하속도 추가.
		FVector BounceVector = -HitVector * (BounceStrength + FallingSpeed);
		// 캐릭터가 무조건 위로 팅겨나가는게 아닌 기존 속도의 반대방향으로 팅겨나가도록
		BounceVector += BeforeHitVelocity;
		// 캐릭터가 부딪힌 반대방향으로 팅겨나가도록
		Character->LaunchCharacter(BounceVector, true, true);

		// Hit이벤트시 점프패드 머터리얼 무색으로 변경
		if (HitComp)
		{
			UMaterialInterface* NewMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_GlowWhite.M_GlowWhite"));
			if (NewMaterial)
			{
				StaticMeshComponent->SetMaterial(0, NewMaterial);
			}
		}
	}
}

void AJumpingPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AMannyAdventureCharacter* Character = Cast<AMannyAdventureCharacter>(OtherActor);
		if (Character)
		{
			FallingSpeed = FMath::Abs(Character->GetVelocity().Z);
		}
	}
}

void AJumpingPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		FallingSpeed = 0.f;
	}
}

void AJumpingPlatform::ResetJumpPlatform()
{
	UMaterialInterface* ResetMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/MI_GlowPurple.MI_GlowPurple"));
	if (ResetMaterial)
	{
		StaticMeshComponent->SetMaterial(0, ResetMaterial);
	}
}





