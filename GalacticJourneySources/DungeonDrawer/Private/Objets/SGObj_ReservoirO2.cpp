// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj_ReservoirO2.h"

ASGObj_ReservoirO2::ASGObj_ReservoirO2()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void ASGObj_ReservoirO2::BeginPlay()
{
	Super::BeginPlay();
}

void ASGObj_ReservoirO2::Interact_Implementation(ASGPlayer_Character* Player)
{

}

void ASGObj_ReservoirO2::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCapsuleBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ASGObj_ReservoirO2::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCapsuleEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

