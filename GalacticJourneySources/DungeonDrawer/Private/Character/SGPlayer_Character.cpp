// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SGPlayer_Character.h"

#include "IPlayerInteraction.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Functions/BP_FunctionLib.h"
#include "Kismet/GameplayStatics.h"
#include "Objets/SGObj_IAInteractible.h"
#include "GameFramework/NavMovementComponent.h"
#include "SGGameInstance.h"

//////////////////////////////////////////////////////////////////////////
// AFP_FirstPersonCharacter

ASGPlayer_Character::ASGPlayer_Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0, 0, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);				// Set so only owner can see mesh
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);	// Attach mesh to FirstPersonCameraComponent
	Mesh1P->bCastDynamicShadow = false;			// Disallow mesh to cast dynamic shadows
	Mesh1P->CastShadow = false;				// Disallow mesh to cast other shadows

	PileSocket = CreateDefaultSubobject<USceneComponent>(TEXT("PileSocket"));
	PileSocket->SetupAttachment(GetMesh(),"Body_Jetpack_Socket");

	//setup des overlap
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASGPlayer_Character::OnCapsuleBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ASGPlayer_Character::OnCapsuleEndOverlap);

	
}

// void ASGPlayer_Character::Tick(float DeltaSeconds)
// {
// 	if(CanInteract == false)
// 	{
// 		TimerInteraction += DeltaSeconds;
// 		if(TimerInteraction > DelayInteraction)
// 			CanInteract = true;
// 	}
// }


//////////////////////////////////////////////////////////////////////////
// Input

void ASGPlayer_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Set up gameplay key bindings

	// Bind jump events
	/*PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);*/

	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ASGPlayer_Character::Interact);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ASGPlayer_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASGPlayer_Character::MoveRight);


	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASGPlayer_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASGPlayer_Character::LookUpAtRate);
}


/*
 *	Colisions
 *
 */
void ASGPlayer_Character::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// si on a collidé avec un objet interactif et qu'il n'y en a pas un en cours
	// if(OtherActor->GetClass()->ImplementsInterface(UIPlayerInteraction::StaticClass()) && InteractibleObject == nullptr)
	// {
	// 	InteractibleObjectActor = OtherActor;
	// }

	//si l'objet implémente IPlayerInteraction on le set comme notre obj interactible et on set son owner
	// if (!InteractibleObjectActor && OtherActor->GetClass()->ImplementsInterface(UIPlayerInteraction::StaticClass()))
	// {
	// 	InteractibleObjectActor = OtherActor;
	// 	TRACE("new interactible object : %s",*InteractibleObjectActor->GetName());
	// 	InteractibleObjectActor->SetOwner(this);
	// }

	if (OtherActor->GetClass()->ImplementsInterface(UIPlayerInteraction::StaticClass()))
	{
		ArrayInteractibleActors.AddUnique(OtherActor);
		TRACE("new interactible object : %s",*OtherActor->GetName());
		OtherActor->SetOwner(this);
	}

}

void ASGPlayer_Character::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//si on a finit collidé avec un objet interactif
	//if (OtherActor->GetClass()->ImplementsInterface(USGIPlayerInteraction::StaticClass()))
	//{
	//	InteractibleObject = nullptr;
	//}
	// if (OtherActor == InteractibleObject)
	// {
	// 	InteractibleObject = nullptr;
	// }
	//si l'objet implémente IPlayerInteraction on le set comme notre obj interactible et on set son owner

	
	// if (InteractibleObjectActor == OtherActor)
	// {
	// 	InteractibleObjectActor = nullptr;
	// 	OtherActor->SetOwner(nullptr);
	// }

	if(ArrayInteractibleActors.Find(OtherActor))
	{
		ArrayInteractibleActors.Remove(OtherActor);
		OtherActor->SetOwner(nullptr);
	}
}


void ASGPlayer_Character::MoveForward(float Value)
{
	if (IsPaused != true)
	{
		if (Value != 0.0f)
		{
			InMovement = true;
			// Add movement in that direction
			AddMovementInput(GetActorForwardVector(), Value);
			//Event de la consommation de fuel en déplacement aérien
			ReduceFuelInMovement();
		}
		InMovement = false;
	}
	
}

void ASGPlayer_Character::MoveRight(float Value)
{
	if (IsPaused != true)
	{
		if (Value != 0.0f)
		{
			InMovement = true;
			// Add movement in that direction
			AddMovementInput(GetActorRightVector(), Value);
			//Event de la consommation de fuel en déplacement aérien
			ReduceFuelInMovement();
		}
		InMovement = false;
	}
	
}

void ASGPlayer_Character::TurnAtRate(float Rate)
{
	// Calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * SensiX * GetWorld()->GetDeltaSeconds());
}

void ASGPlayer_Character::LookUpAtRate(float Rate)
{
	// Calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * SensiY * GetWorld()->GetDeltaSeconds());
}

//interaction avec un objet : appel de son interface
void ASGPlayer_Character::Interact()
{

	// 	TRACESCREEN("PlayerInteract");
	// 	InteractibleObject->PlayerInteraction();
	// 	//TRACESCREEN("InteractPlayer");
	// 	//ISGIPlayerInteraction::Execute_Interact(InteractibleObject);
	// 	//InteractibleObject->playerInteraction->CallServer(this);
	// 	//UE_LOG(LogTemp, Warning, TEXT(" interact ! "));
 //
	// FHitResult hitResult;
	// FCollisionQueryParams params;
	// params.AddIgnoredActor(this);
	// UCameraComponent* playerCam = this->GetFirstPersonCameraComponent();
	// 	
	// this->GetWorld()->LineTraceSingleByChannel(hitResult, playerCam->GetComponentLocation(),
 //        (playerCam->GetComponentLocation() + playerCam->GetForwardVector() * 1000),
 //        ECollisionChannel::ECC_Visibility);
 //
	// ASGObj* obj = Cast<ASGObj>(hitResult.GetActor());
	// if(obj)
	// {
	// 	obj->SetOwner(this);
	// }

	// if(InteractibleObjectActor)
	// {
	// 	ServerSetOwnerOnClick(this,InteractibleObjectActor);
	// 	// TRACE("Set owner of interactible actor to %s",*this->GetName())
	// 	IIPlayerInteraction::Execute_Interact(InteractibleObjectActor,this);
	// }
	//
	// if(!CanInteract)
	// 	return;
	//
	// TRACE("Player interact !");
	
	TArray<AActor*> tmp = ArrayInteractibleActors;
	
	for (AActor* InteractActor : tmp)
	{
		if(InteractActor)
		{
			ServerSetOwnerOnClick(this,InteractActor);
			IIPlayerInteraction::Execute_Interact(InteractActor,this);
		}
		/*else
		{
			ArrayInteractibleActors.Remove(InteractActor);
		}*/
	}

	// CanInteract = false;
}

void ASGPlayer_Character::MulticastSetOwnerOnClick_Implementation(ASGPlayer_Character* Player,AActor* Object)
{
	if(Object)
		Object->SetOwner(Player);
}

void ASGPlayer_Character::ServerSetOwnerOnClick_Implementation(ASGPlayer_Character* Player,AActor* Object)
{
	MulticastSetOwnerOnClick(Player,Object);
}

void ASGPlayer_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGPlayer_Character, CharacterColor);
}