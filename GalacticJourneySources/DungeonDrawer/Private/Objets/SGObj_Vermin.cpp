// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_Vermin.h"
#include "Character/SGPlayer_Character.h"
#include "Net/UnrealNetwork.h"
#include "DungeonDrawer/DungeonDrawer.h"

ASGObj_Vermin::ASGObj_Vermin()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

void ASGObj_Vermin::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
}

void ASGObj_Vermin::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// void ASGObj_Vermin::PlayerInteraction()
// {
// 	RunOnServer();
// }
//
// void ASGObj_Vermin::RunOnClients_Implementation()
// {
// 	TRACESCREEN("RunOnClient");
// 	//this->K2_DestroyActor();
// 	Destroy();
// }

// void ASGObj_Vermin::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	Super::OnCapsuleBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
// 	//TRACESCREEN("In");
// }
//
// void ASGObj_Vermin::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// 	Super::OnCapsuleEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
// 	//TRACESCREEN("Out");
// }