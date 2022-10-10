// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_VerminV2.h"

#include "GeneratedCodeHelpers.h"
#include "Functions/BP_FunctionLib.h"
#include "Objets/SGObj_SpawnerVermin.h"

ASGObj_VerminV2::ASGObj_VerminV2()
{
	SkeletalMeshRobot = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RobotSkeletalMesh"));
	SkeletalMeshRobot->SetupAttachment(RootComponent);
}

void ASGObj_VerminV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerNear)
	{
		if (SkeletalMeshRobot == UBP_FunctionLib::GetSkeletalMeshLookedAtByPlayerWithDistance(PlayerNear, 300))
		{
			IsLookedAt = true;
			SkeletalMeshRobot->SetRenderCustomDepth(true);
		}
		else
		{
			IsLookedAt = false;
			SkeletalMeshRobot->SetRenderCustomDepth(false);
		}
	}
}

void ASGObj_VerminV2::Interact_Implementation(ASGPlayer_Character* Player)
{
	//useless ?
	this->SetOwner(Player);

	SetOwnerVermineSpawnerServer(Player);

	RefSpawner->DeactivateVermine(this);
}

void ASGObj_VerminV2::SetOwnerVermineSpawnerServer_Implementation(ASGPlayer_Character* Player)
{
	TRACE("SetOwnerVermineSpawner Server")
	RefSpawner->SetOwner(Player);

	SetOwnerVermineSpawnerMulticast(Player);
}

void ASGObj_VerminV2::SetOwnerVermineSpawnerMulticast_Implementation(ASGPlayer_Character* Player)
{
	TRACE("SetOwnerVermineSpawner Multicast")

	RefSpawner->SetOwner(Player);
	RefSpawner->AddPlayerRepair(Player);
	// if (HasAuthority())
	// 	RefSpawner->RequestServerDestroy(this);
}

void ASGObj_VerminV2::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGObj_VerminV2, RefSpawner);
}

void ASGObj_VerminV2::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == PlayerNear)
	{
		PlayerNear = nullptr;
	}
}

void ASGObj_VerminV2::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                            const FHitResult& SweepResult)
{
	ASGPlayer_Character* Player_Character = Cast<ASGPlayer_Character>(OtherActor);

	if (Player_Character)
	{
		PlayerNear = Player_Character;
	}
}
