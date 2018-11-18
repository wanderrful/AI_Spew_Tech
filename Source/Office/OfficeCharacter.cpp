// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "OfficeCharacter.h"
#include "OfficeProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactable.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AOfficeCharacter

AOfficeCharacter::AOfficeCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	BaseLookUpRate = 500.f;

	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	CameraRoot->SetupAttachment(GetCapsuleComponent());
	CameraRoot->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(CameraRoot);
	//FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Constraint"));
	Constraint->SetupAttachment(FirstPersonCameraComponent);

	ConnectionPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("ConnectionPoint"));
	ConnectionPoint->SetupAttachment(FirstPersonCameraComponent);
	ConnectionPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/*
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	*/
	// Default offset from the character location for projectiles to spawn
	//GunOffset = FVector(100.0f, 0.0f, 10.0f);

	bBlocked = false;
	bCanWalk = false;
}



void AOfficeCharacter::BeginPlay()
{
	  
	Super::BeginPlay();
	Constraint->OnConstraintBroken.AddDynamic(this, &AOfficeCharacter::OnBreak);

	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	
	
	//Mesh1P->SetHiddenInGame(false, true);

}

//////////////////////////////////////////////////////////////////////////
// Input

void AOfficeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AOfficeCharacter::PickUp);
	PlayerInputComponent->BindAction("PickUp", IE_Released, this, &AOfficeCharacter::Drop);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &AOfficeCharacter::Use);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AOfficeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOfficeCharacter::MoveRight);
	PlayerInputComponent->BindAxis("ZoomItem", this, &AOfficeCharacter::ZoomItem);
	PlayerInputComponent->BindAxis("MoveRight", this, &AOfficeCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AOfficeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AOfficeCharacter::LookUpAtRate);


	

	
}

void AOfficeCharacter::AddControllerPitchInput(float Val) {
	if (!bBlocked) Super::AddControllerPitchInput(Val);
}

void AOfficeCharacter::AddControllerYawInput(float Val) {
	if (!bBlocked) Super::AddControllerYawInput(Val);
}

void AOfficeCharacter::MoveForward(float Value)
{
	if (!bBlocked) {
		if (Value != 0.0f)
		{
			// add movement in that direction
			AddMovementInput(GetActorForwardVector(), Value);
		}
	}
}

void AOfficeCharacter::MoveRight(float Value)
{
	if (!bBlocked) {
		if (Value != 0.0f)
		{
			// add movement in that direction
			AddMovementInput(GetActorRightVector(), Value);
		}
	}
}

void AOfficeCharacter::ZoomItem(float Val) 
{
	if (!ItemHolding) return;
	InitialHoldDistance += Val * 4.0;
	InitialHoldDistance = FMath::Clamp<float>(InitialHoldDistance, 10.0, 250.0);
}

void AOfficeCharacter::UnlockWalk() {
	bCanWalk = true;
	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Walking;
}

void AOfficeCharacter::LockWalk() {
	bCanWalk = false;
	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_None;
}



void AOfficeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!bBlocked) AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AOfficeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!bBlocked) AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AOfficeCharacter::PickUp() {
	if(!ItemOnFocus || bBlocked) return;
	if (ItemOnFocus->IsA(AInteractable::StaticClass()) && !Cast<AInteractable>(ItemOnFocus)->CanPickup()) {
		Use();
		return;
	}
	
	ItemHolding = ItemOnFocus;
	Constraint->SetRelativeLocation(FVector(InitialHoldDistance,0,0));
	ConnectionPoint->SetRelativeLocation(FVector(InitialHoldDistance, 0, 0));
	Constraint->SetConstrainedComponents(ConnectionPoint, NAME_None, ComponentOnFocus, NAME_None);
	/*
	ItemHolding->Hitbox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	ItemHolding->Hitbox->SetSimulatePhysics(false);
	*/

	

}

void AOfficeCharacter::OnBreak(int32 id) {
	Drop();
}

void AOfficeCharacter::Drop() {

	if(!ItemHolding) return;
	/*
	ItemHolding->Hitbox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	ItemHolding->Hitbox->SetSimulatePhysics(true);
	*/
	Constraint->BreakConstraint();
	ItemHolding = nullptr;
	
}

void AOfficeCharacter::Use() {
	if (bBlocked) return;
	if (ItemHolding) {
		if (ItemHolding->IsA(AInteractable::StaticClass())) {
			Cast<AInteractable>(ItemHolding)->OnUse();
		}
		else {
			Constraint->BreakConstraint();
			FRotator R = FirstPersonCameraComponent->GetComponentToWorld().GetRotation().Rotator();
			Cast<UPrimitiveComponent>(ItemHolding->GetRootComponent())->AddForce(R.RotateVector(FVector(ThrowForce,0.0,0.0)),NAME_None,true);
			ItemHolding = nullptr;
		}
	}
	else if (ItemOnFocus) {
		if(ItemOnFocus->IsA(AInteractable::StaticClass()) && !Cast<AInteractable>(ItemOnFocus)->CanPickup()) Cast<AInteractable>(ItemOnFocus)->OnUse();
	}
	
}

void  AOfficeCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!Cast<APlayerController>(GetController())) return;

	FHitResult Result;
	FVector Location = FirstPersonCameraComponent->GetComponentToWorld().GetLocation();
	FVector Target, Direction;
	FRotator Rotation = FirstPersonCameraComponent->GetComponentToWorld().GetRotation().Rotator();
	AActor* OldFocus = ItemOnFocus;
	FVector2D ScreenCenter;
	GetWorld()->GetGameViewport()->GetViewportSize(ScreenCenter);
	ScreenCenter /= 2;
	UGameplayStatics::DeprojectScreenToWorld(Cast<APlayerController>(GetController()), ScreenCenter, Target, Direction);


	/*
	if (ItemHolding) {
		FRotator NewRotaiton = InitialHoldViewRotation - Direction.Rotation();
		NewRotaiton.Pitch = -NewRotaiton.Pitch;
		NewRotaiton.Roll = 0;
		ItemHolding->SetActorLocation(Location + (Direction*InitialHoldDistance));
		ItemHolding->SetActorRotation(InitialHoldRotation - (InitialHoldViewRotation-Direction.Rotation()));
		return;
	}
	*/
	
	if (ItemHolding) {
		//Constraint->SetWorldLocation(Location + (Direction*InitialHoldDistance));
		Constraint->SetRelativeLocation(FVector(InitialHoldDistance, 0, 0));
		ConnectionPoint->SetRelativeLocation(FVector(InitialHoldDistance, 0, 0));
	}
	
	if (!ItemHolding) {
		ItemOnFocus = nullptr;
		ComponentOnFocus = nullptr;
		GetWorld()->LineTraceSingleByObjectType(Result, Location, Location + (Direction*250.0), FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel2));
		InitialHoldLocation = Location;
		InitialHoldDistance = Result.Distance;
		//InitialHoldRotation = ItemHolding->GetActorRotation();
		InitialHoldViewRotation = FirstPersonCameraComponent->GetComponentToWorld().GetRotation().Rotator();
		if (Result.GetActor()) {
			ItemOnFocus = Result.GetActor();
			if (Result.GetComponent()) ComponentOnFocus = Result.GetComponent();
			else ComponentOnFocus = Cast<UPrimitiveComponent>(ItemOnFocus->GetRootComponent());
		}
	}
}

bool AOfficeCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	
	return false;
}
