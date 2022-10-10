// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "IPlayerInteraction.h"
#include "SGObj_IAInteractible.h"
#include "SGObj_MotorPump.generated.h"

class ASGPlayer_Character;
/**
 *
 */
UCLASS()
class DUNGEONDRAWER_API ASGObj_MotorPump : public ASGObj_IAInteractible, public IIPlayerInteraction
{
	GENERATED_BODY()

public:
	ASGObj_MotorPump();

	virtual void BeginPlay() override;

	// virtual void PlayerInteraction() override;
	void Interact(ASGPlayer_Character* Player);
	virtual void Interact_Implementation(ASGPlayer_Character* Player) override;

	virtual void ServerRPCDoAction_Implementation() override;

	virtual void Tick(float DeltaSeconds) override;
	//virtual void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//virtual void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(Server, Reliable)
		void RunOnServerPump(int _buttonPress, ASGPlayer_Character* player);

	UFUNCTION(NetMulticast, Reliable)
		void RunOnClientPump(int _buttonPress, ASGPlayer_Character* player);
	UFUNCTION(BlueprintImplementableEvent)
		void DownSmokeDesactivate(int smoke);
	UFUNCTION(BlueprintImplementableEvent)
		void UpSmokeActivate();
	UFUNCTION(BlueprintImplementableEvent)
		void RepeiredPump();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MotorPump;

private:

	UPROPERTY(EditAnywhere)
		TArray<UStaticMeshComponent*> Buttons;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ButtonTop;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ButtonLeft;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ButtonRight;

	UPROPERTY(EditAnyWhere)
		FVector BasePoseTop = FVector{ -15.0f, 0.0f, 400.0f };
	UPROPERTY(EditAnyWhere)
		FVector BasePoseLeft = FVector{ -55.0f, -160.0f, 35.0f };
	UPROPERTY(EditAnyWhere)
		FVector BasePoseRight = FVector{ -55.0f, 160.0f, 35.0f };

	UPROPERTY(EditAnyWhere)
		USoundBase* Pump_On;
	UPROPERTY(EditAnyWhere)
		USoundBase* Pump_Off;
	UPROPERTY(EditAnyWhere)
		TArray<USoundBase*> Pump_Hit;
	UPROPERTY(EditAnywhere)
		USoundBase* Pump_Top_Hit;
	UPROPERTY(EditAnywhere)
		USoundBase* Pump_Hit_No_Interact;
	UPROPERTY(EditAnywhere)
		USoundBase* PumpRepared;

	int buttonPress = 0;
	int nbPressLeft = 0;
	int nbPressRight = 0;
};
