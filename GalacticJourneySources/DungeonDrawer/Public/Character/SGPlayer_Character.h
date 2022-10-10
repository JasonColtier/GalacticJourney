// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGPlayer_Character.generated.h"

class ASGObj_IAInteractible;
class ASGObj_Pile;
class UCameraComponent;
class USGGameInstance;

UCLASS()
class DUNGEONDRAWER_API ASGPlayer_Character : public ACharacter
{
	GENERATED_BODY()

public:
		/** Pawn mesh: 1st person view (arms; seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(BlueprintReadWrite, Replicated)
	UMaterial* CharacterColor;

	UPROPERTY(BlueprintReadWrite)
	USGGameInstance* GameInstance;

	UPROPERTY(BlueprintReadWrite)
	float SensiX;

	UPROPERTY(BlueprintReadWrite)
	float SensiY;
	


public:
	// Sets default values for this character's properties
	ASGPlayer_Character();

	// virtual void Tick(float DeltaSeconds) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* InteractibleObjectActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> ArrayInteractibleActors;

	//un scene component pour accueillir la pile une fois qu'on l'a ramassée
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* PileSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ASGObj_Pile* HoldedPile;

	UFUNCTION()
		void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "LaunchSabotate"))
		void LaunchSabotate();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void HoldHammerBeginOverlap();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void HoldHammerEndOverlap2();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void HoldScrewdriverBeginOverlap();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void HoldScrewdriverEndOverlap2();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void AnimInteract2();


protected:
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void Interact();

	UFUNCTION(Server, Reliable)
		void ServerSetOwnerOnClick(ASGPlayer_Character* Player, AActor* Object);

	UFUNCTION(NetMulticast, Reliable)
		void MulticastSetOwnerOnClick(ASGPlayer_Character* Player, AActor* Object);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool DoSecondJump = false;

	UPROPERTY(BlueprintReadWrite)
		bool InMovement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Fuel;

	//quel mesh parmis ceux pouvant accueillir les piles est ce qu'on regarde actuellement ?
	UPROPERTY()
		UStaticMeshComponent* LookedAtMesh;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ReduceFuelInMovement"))
		void ReduceFuelInMovement();

	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPaused;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHoldingHammer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsHoldingScrewdriver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInteracting;


public:

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:

	UPROPERTY()
		bool CanInteract = true;

	UPROPERTY()
		float TimerInteraction = 0;

	UPROPERTY()
		float DelayInteraction = 0.1f;
};
