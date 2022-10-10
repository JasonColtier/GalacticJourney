// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/SGObj.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ASGObj::ASGObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRootComponent;
	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	CapsuleCollider->SetupAttachment(SceneRootComponent);
	
	//setup des overlap
	CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &ASGObj::OnCapsuleBeginOverlap);
	CapsuleCollider->OnComponentEndOverlap.AddDynamic(this, &ASGObj::OnCapsuleEndOverlap);
	
	//par défaut tous les objets doivent pouvoir répliquer leurs états et leurs actions pour tous les joueurs
	SetReplicates(true);
}

void ASGObj::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASGObj::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void ASGObj::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void ASGObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

