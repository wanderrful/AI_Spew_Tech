#include "OfficePlayerController.h"
#include "OfficeStatics.h"
#include "OfficeGameMode.h"
#include "OfficeScreen.h"
#include "Engine/Console.h"
#include "Engine/World.h"
#include "Engine/GameViewportClient.h"

FString AOfficePlayerController::ConsoleCommand(const FString& Command, bool bWriteToLog) {

	TArray<FString> S;
	Command.ParseIntoArray(S,TEXT(" "));
	S[0] = S[0].ToLower();
	UConsole* Console = GetWorld()->GetGameViewport()->ViewportConsole;
#if !WITH_EDITOR
	Console->HistoryBuffer.Empty();
#endif
	if (UOfficeStatics::GetOfficeGameMode(GetWorld())->Screen) {
		if (S[0] == "chat") {
			UOfficeStatics::GetOfficeGameMode(GetWorld())->Screen->SummonIRC();
			return "";
		}
		if (S[0] == "webbrowser") {

			UOfficeStatics::GetOfficeGameMode(GetWorld())->Screen->ToggleDeadWeb();

			/*
			if (S.Num() == 1) Console->OutputText("Usage: DeadWeb <password>");
			else if (S[1] == UOfficeStatics::GetOfficeGameMode(GetWorld())->DecodedCode) UOfficeStatics::GetOfficeGameMode(GetWorld())->Screen->ToggleDeadWeb();
			else Console->OutputText("DeadWeb: Wrong Password");
			return "";
			*/
		}
	}
	if (S[0] == "quit" || S[0] == "exit") {
		if (UOfficeStatics::GetOfficeGameMode(this)->bUnlockQuit) Super::ConsoleCommand(Command, bWriteToLog);
		Console->OutputText("Quit request denied");
		return "";
	}
	if (S[0] == "restartlevel") {
		Console->OutputText("Time reversal impossible");
		return "";
	}
	if (S[0] == "fly") {
		Console->OutputText("You feel tied to the chair");
		return "";
	}
	if (S[0] == "walk") {
		Console->OutputText("You can't walk anyway");
		return "";
	}
	if (S[0] == "god") {
		Console->OutputText("Gods can't exist is this world");
		return "";
	}

#if WITH_EDITOR
	if (S[0] == "generatecode") {
		UOfficeStatics::GetOfficeGameMode(GetWorld())->GenerateCode();
		UOfficeStatics::GetOfficeGameMode(GetWorld())->SaveConfig();
		UOfficeStatics::GetOfficeGameMode(GetWorld())->DecodeCode();
		Console->OutputText(UOfficeStatics::GetOfficeGameMode(GetWorld())->DecodedCode);
		Console->OutputText(UOfficeStatics::GetOfficeGameMode(GetWorld())->DecodedBookCode[0]);
		Console->OutputText(UOfficeStatics::GetOfficeGameMode(GetWorld())->DecodedBookCode[1]);
		Console->OutputText(UOfficeStatics::GetOfficeGameMode(GetWorld())->DecodedBookCode[2]);
		Console->OutputText(UOfficeStatics::GetOfficeGameMode(GetWorld())->DecodedBookCode[3]);
		Console->OutputText(UOfficeStatics::GetOfficeGameMode(GetWorld())->DecodedBookCode[4]);
		return "";
	}

	if (S[0] == "showcode") {
		Console->OutputText(UOfficeStatics::GetOfficeGameMode(GetWorld())->DecodedCode);
		Console->OutputText(UOfficeStatics::GeBookCode(0,this));
		Console->OutputText(UOfficeStatics::GeBookCode(1, this));
		Console->OutputText(UOfficeStatics::GeBookCode(2, this));
		Console->OutputText(UOfficeStatics::GeBookCode(3, this));
		Console->OutputText(UOfficeStatics::GeBookCode(4, this));
		return "";
	}

	return Super::ConsoleCommand(Command, bWriteToLog);
#endif

	if (S[0] == "stat" && S[1] == "fps") {
		return Super::ConsoleCommand(Command, bWriteToLog);
	}

	if (S[0] == "viewmode") {
		Super::ConsoleCommand("r.ForceDebugViewModes 1", bWriteToLog);
		return Super::ConsoleCommand(Command, bWriteToLog);
	}

	if (S[0] == "viewmode") {
		Super::ConsoleCommand("r.ForceDebugViewModes 1", bWriteToLog);
		return Super::ConsoleCommand(Command, bWriteToLog);
	}

	return "";
}

void AOfficePlayerController::BeginPlay() {
	Super::BeginPlay();
}