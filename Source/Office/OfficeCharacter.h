// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OfficeCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AOfficeCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CameraRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup Constraint", meta = (AllowPrivateAccess = "true"))
	class UPhysicsConstraintComponent* Constraint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup Constraint", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* ConnectionPoint;


public:
	AOfficeCharacter();
	virtual void AddControllerPitchInput(float Val) override;
	virtual void AddControllerYawInput(float Val) override;

protected:
	virtual void BeginPlay();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
	float ThrowForce;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	bool bBlocked;

protected:

	void MoveForward(float Val);
	void MoveRight(float Val);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void PickUp();
	void Drop();

	void Use();

	UFUNCTION()
	void OnBreak(int32 id);

	UFUNCTION()
	void ZoomItem(float Val);

	UFUNCTION(BlueprintCallable)
	void UnlockWalk();

	UFUNCTION(BlueprintCallable)
	void LockWalk();

	UPROPERTY(VisibleAnywhere)
	class AActor* ItemOnFocus;

	UPROPERTY(VisibleAnywhere)
	class UPrimitiveComponent* ComponentOnFocus;
	
	UPROPERTY(VisibleAnywhere)
	class AActor* ItemHolding;

	UPROPERTY(VisibleAnywhere)
	float InitialHoldDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanWalk;

	UPROPERTY(VisibleAnywhere)
	FRotator InitialHoldRotation;


	UPROPERTY(VisibleAnywhere)
	FVector InitialHoldLocation;

	UPROPERTY(VisibleAnywhere)
	FRotator InitialHoldViewRotation;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Office Game")
	void OnGameOver();

	
protected:

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	virtual void Tick(float DeltaTime) override;

};

