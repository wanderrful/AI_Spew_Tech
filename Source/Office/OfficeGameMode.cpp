// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "OfficeGameMode.h"
#include "OfficeHUD.h"
#include "OfficeScreen.h"
#include "OfficeRobot.h"
#include "OfficeCharacter.h"
#include "OfficePlayerController.h"
#include "OfficeStatics.h"
#include "Engine/Console.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "AIController.h"
#include "Engine/GameViewportClient.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"

AOfficeGameMode::AOfficeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AOfficeHUD::StaticClass();
	PlayerControllerClass = AOfficePlayerController::StaticClass();
	Lives = 3;
	bUnlockQuit = false;
}

void AOfficeGameMode::BeginPlay() {

	Super::BeginPlay();
	//DonTKnowWhatThisDo.Empty();
	if (DonTKnowWhatThisDo.Num() != 6) {
		GenerateCode();
		SaveConfig();
	}

	

	DecodeCode();

#if UE_BUILD_SHIPPING
	// Create the viewport's console.
	GetWorld()->GetGameViewport()->ViewportConsole = NewObject<UConsole>(GetWorld()->GetGameViewport());
	// register console to get all log messages
	GLog->AddOutputDevice(GetWorld()->GetGameViewport()->ViewportConsole);
	//GetWorld()->GetGameViewport()->ViewportConsole->InputKey(0, EKeys::Tilde, IE_Pressed);
#endif
	GetWorld()->GetGameViewport()->ViewportConsole->OutputText(TEXT("Bewere of the man speaking in Sam's voice"));
}

void AOfficeGameMode::RegisterScreenWidget(UOfficeScreen* Widget) {
	Screen = Widget;
	Screen->SetOwningLocalPlayer(GetWorld()->GetFirstLocalPlayerFromController());
	
}

void AOfficeGameMode::RaportMousePosition(FVector2D Pos) {
	if (Screen) Screen->OnMousePositionRaported(Pos);
}

void AOfficeGameMode::GenerateCode() {
	DonTKnowWhatThisDo.Empty();
	DonTKnowWhatThisDo.AddDefaulted(6);
	for (int i = 0; i < 6; i++) {
		DonTKnowWhatThisDo[i] = FMath::RandRange(0.0f, 1.0f);
	}
}

void AOfficeGameMode::StartPerforamceDescrese() {
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AOfficeGameMode::DecreaseCounter, true, 1.0);
}

void AOfficeGameMode::GoodAnwser() {
	TotalCounter++;
	Performance++;
	
}

void AOfficeGameMode::LossLife() {

	Lives--;
}

void AOfficeGameMode::BadAnwser() {
	Performance /= 2.0;
}

void AOfficeGameMode::DecreaseCounter() {
	Performance -= 1.0f/15.0f;
	float OldPerformance;
	OldPerformance = Performance;
	Performance = FMath::Max(0.0f, Performance);
	if (!UOfficeStatics::GetRobot(this)->bItsZapTime && Performance <= 0.0) {
		UOfficeStatics::GetRobot(this)->MoveToZap();
	}
}


void AOfficeGameMode::DecodeCode() {

	DecodedCode = "0000";
	DecodedBookCode.Empty();
	DecodedBookCode.Add("0000");
	DecodedBookCode.Add("0000");
	DecodedBookCode.Add("0000");
	DecodedBookCode.Add("0000");
	DecodedBookCode.Add("0000");

	for (int i = 0; i < 6; i++) {
		if (FMath::IsNearlyZero(DonTKnowWhatThisDo[i]) || FMath::IsNearlyEqual(DonTKnowWhatThisDo[i], 1.0f)) {
			GenerateCode();
			SaveConfig();
		}
		if (DonTKnowWhatThisDo[i] < 0.0f || DonTKnowWhatThisDo[i] > 1.0f) {
			GenerateCode();
			SaveConfig();
		}

	}



	DecodedCode[0] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[2] + DonTKnowWhatThisDo[4]) / 2) * 10)))[0];
	DecodedCode[1] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[1] + DonTKnowWhatThisDo[5]) / 2) * 1000)))[1];
	DecodedCode[2] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[3] + DonTKnowWhatThisDo[5]) / 2) * 10000)))[2];
	DecodedCode[3] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[0] + DonTKnowWhatThisDo[3]) / 2) * 10)))[0];

	DecodedBookCode[0][0] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[0] + DonTKnowWhatThisDo[4]) / 2) * 100)))[0];
	DecodedBookCode[0][1] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[3] + DonTKnowWhatThisDo[5]) / 2) * 100)))[0];
	DecodedBookCode[0][2] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[1] + DonTKnowWhatThisDo[1]) / 2) * 1000)))[0];
	DecodedBookCode[0][3] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[1] + DonTKnowWhatThisDo[3]) / 2) * 100)))[0];

	DecodedBookCode[1][0] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[0] + DonTKnowWhatThisDo[2]) / 2) * 100)))[0];
	DecodedBookCode[1][1] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[1] + DonTKnowWhatThisDo[5]) / 2) * 10)))[0];
	DecodedBookCode[1][2] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[2] + DonTKnowWhatThisDo[3]) / 2) * 100)))[0];
	DecodedBookCode[1][3] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[5] + DonTKnowWhatThisDo[5]) / 2) * 10)))[0];

	DecodedBookCode[2][0] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[5] + DonTKnowWhatThisDo[4]) / 2) * 1000)))[0];
	DecodedBookCode[2][1] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[0] + DonTKnowWhatThisDo[0]) / 2) * 1)))[0];
	DecodedBookCode[2][2] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[3] + DonTKnowWhatThisDo[0]) / 2) * 100)))[0];
	DecodedBookCode[2][3] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[1] + DonTKnowWhatThisDo[3]) / 2) * 10)))[0];

	DecodedBookCode[3][0] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[0] + DonTKnowWhatThisDo[1]) / 2) * 10)))[0];
	DecodedBookCode[3][1] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[1] + DonTKnowWhatThisDo[2]) / 2) * 1000)))[0];
	DecodedBookCode[3][2] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[2] + DonTKnowWhatThisDo[3]) / 2) * 1)))[0];
	DecodedBookCode[3][3] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[4] + DonTKnowWhatThisDo[5]) / 2) * 10)))[0];

	DecodedBookCode[4][0] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[5] + DonTKnowWhatThisDo[1]) / 2) * 10)))[0];
	DecodedBookCode[4][1] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[5] + DonTKnowWhatThisDo[2]) / 2) * 10)))[0];
	DecodedBookCode[4][2] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[5] + DonTKnowWhatThisDo[3]) / 2) * 10)))[0];
	DecodedBookCode[4][3] = (*FString::FromInt(FMath::RoundToInt(((DonTKnowWhatThisDo[5] + DonTKnowWhatThisDo[4]) / 2) * 10)))[0];

	for (int i = 0; i < 5; i++) {
		if (!DecodedBookCode[i].IsNumeric() || DecodedBookCode[i].Len() != 4) {
			GenerateCode();
			DecodeCode();
			return;
		}

		for (int j = 0; j < 5; j++) {
			if (i != j && DecodedBookCode[i] == DecodedBookCode[j]) {
				GenerateCode();
				DecodeCode();
				return;
			}
		}
	}



}
