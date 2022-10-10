// Fill out your copyright notice in the Description page of Project Settings.


#include "IA/Pawn/SGIA_Pawn.h"

#include "GeneratedCodeHelpers.h"

// Sets default values
ASGIA_Pawn::ASGIA_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASGIA_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASGIA_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASGIA_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASGIA_Pawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGIA_Pawn,AIInteracObjectsPawn);
}

