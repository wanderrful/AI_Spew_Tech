#include "OfficeStatics.h"
#include "OfficeGameMode.h"
#include "OfficeRobot.h"
#include "OfficeCharacter.h"
#include "RobotTargetPoint.h"
#include "AIController.h"
#include "SlateApplication.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"


AOfficeGameMode* UOfficeStatics::GetOfficeGameMode(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return Cast<AOfficeGameMode>(World->GetAuthGameMode());

}

FString UOfficeStatics::GenerateRandomString() {

	FString S = "";

	for (int i = 0; i < 6; i++) {
		float N = FMath::RandRange(0.0f, 1.0f);
		if (N < 0.5) {
			S += FString::FromInt(FMath::RandRange(0, 9));
		}
		else {
			S += FString::Chr(0x60 + FMath::RandRange(0x01,0x1A));
		}

	}

	return S;

}

FString UOfficeStatics::FloatToSting(float Float) {
	int32 full;
	float frac;
	full = FMath::FloorToInt(Float);
	frac = FMath::Frac(Float);
	return FString::FromInt(full) + "." + FString::SanitizeFloat(frac,2).Left(4).Right(2);
}

void UOfficeStatics::ClearKeyboardFocus() {
	FSlateApplication::Get().ClearAllUserFocus(EFocusCause::Cleared);
	FSlateApplication::Get().ClearKeyboardFocus(EFocusCause::Cleared);
}

FString UOfficeStatics::GetSystemUsername() {
	return FPlatformMisc::GetLoginId();
}

void UOfficeStatics::RobotGoTo(const UObject* WorldContextObject, ERoboNavPoints Destination) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	AOfficeGameMode* GM = UOfficeStatics::GetOfficeGameMode(World);
	if (GM && GM->Robot) {
		GM->Robot->MoveTo(Destination);
	}
}

AOfficeCharacter* UOfficeStatics::GetOffcieCharacter(const UObject* WorldContextObject) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return Cast<AOfficeCharacter>(World->GetFirstPlayerController()->GetPawn());
}

AOfficeRobot* UOfficeStatics::GetRobot(const UObject* WorldContextObject) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return UOfficeStatics::GetOfficeGameMode(World)->Robot;
}

void UOfficeStatics::RobotPlayVoice(const UObject* WorldContextObject, class USoundBase* Sound, FTimerDynamicDelegate Delegate) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	AOfficeGameMode* GM = UOfficeStatics::GetOfficeGameMode(World);
	if (GM && GM->Robot) {
		GM->Robot->PlayVoice(Sound, Delegate);
	}

}

void UOfficeStatics::RobotWait(const UObject* WorldContextObject, float Time, FTimerDynamicDelegate Delegate) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	AOfficeGameMode* GM = UOfficeStatics::GetOfficeGameMode(World);
	if (GM && GM->Robot) {
		GM->Robot->Wait(Time, Delegate);
	}

}

AAIController* UOfficeStatics::GetRobotAI(const UObject* WorldContextObject) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return UOfficeStatics::GetOfficeGameMode(World)->RobotAI;
}

FString UOfficeStatics::GetWhiteSpaceCode(const UObject* WorldContextObject) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return UOfficeStatics::GetOfficeGameMode(World)->DecodedCode;
}

FString UOfficeStatics::GeBookCode(int32 ID, const UObject* WorldContextObject) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (UOfficeStatics::GetOfficeGameMode(World)->DecodedBookCode.Num() != 5) return "0000";
	if (ID < 0 || ID > 5) return "0000";
	return UOfficeStatics::GetOfficeGameMode(World)->DecodedBookCode[ID];
}