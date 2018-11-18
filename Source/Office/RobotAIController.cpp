#include "RobotAIController.h"
#include "OfficeRobot.h"
#include "OfficeEnums.h"
#include "Components/AudioComponent.h"

void ARobotAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result) {
	Super::OnMoveCompleted(RequestID, Result);

	if (Robot->MovmentEnd) {
		Robot->MovementAudio->Stop();
		Robot->MovementAudio->SetSound(Robot->MovmentEnd);
		Robot->MovementAudio->Play();
	}

	if (Result.Code == EPathFollowingResult::Success) {
		Robot->CurrentPosition = Robot->CurrentDestination;
		Robot->CurrentDestination = ERoboNavPoints::Unknown;
		Robot->bOnTheMove = false;
	}
	if (Result.Code == EPathFollowingResult::Blocked || Result.Code == EPathFollowingResult::OffPath) {
		Robot->MoveTo(Robot->PreviuesPosition);
	}

	if (Robot->bItsZapTime) {
		Robot->OnAboutToZap();
	}

}

void ARobotAIController::Possess(APawn * InPawn) {
	Super::Possess(InPawn);
	Robot = Cast<AOfficeRobot>(InPawn);
}