#include "OfficeRobot.h"
#include "OfficeStatics.h"
#include "OfficeGameMode.h"
#include "OfficeCharacter.h"
#include "AIController.h"
#include "RobotTargetPoint.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SkeletalMeshComponent.h"

AOfficeRobot::AOfficeRobot() {
	VoiceOutput = CreateDefaultSubobject<UAudioComponent>(FName("Voice"));
	VoiceOutput->SetupAttachment(RootComponent);
	MovementAudio = CreateDefaultSubobject<UAudioComponent>(FName("Movment"));
	MovementAudio->SetupAttachment(RootComponent);
	GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, false));
	PostProcess = CreateDefaultSubobject<UPostProcessComponent>(FName("PostProcess"));
	PostProcess->BlendRadius = 1.0;
	PostProcess->bUnbound = false;

}

void AOfficeRobot::PlayVoiceWithoutDelegate(class USoundBase* Sound) {
	if (!Sound) return;
	if (VoiceOutput->IsPlaying()) VoiceOutput->Stop();
	VoiceOutput->SetSound(Sound);
	VoiceOutput->Play();
}

void AOfficeRobot::BeginPlay() {

	
	UOfficeStatics::GetOfficeGameMode(this)->Robot = this;
	UOfficeStatics::GetOfficeGameMode(this)->RobotAI = Cast<AAIController>(GetController());
	Super::BeginPlay();
	//VoiceOutput->AttenuationSettings->Attenuation.FalloffDistance = 300.f;
	//MovementAudio->AttenuationSettings->Attenuation.FalloffDistance = 300.f;

}

void AOfficeRobot::MoveTo(ERoboNavPoints Destination) {
	AOfficeGameMode* GM = UOfficeStatics::GetOfficeGameMode(this);
	if (!GM->NavPoints.Contains(Destination)) return;
	FAIMoveRequest Request;
	Request.SetGoalActor(GM->NavPoints[Destination]);
	Request.SetReachTestIncludesGoalRadius(true).SetAcceptanceRadius(20.0);
	GM->RobotAI->MoveTo(Request);
	PreviuesPosition = CurrentPosition;
	CurrentDestination = Destination;
	bOnTheMove = true;
	if(MovmentStart) {
		MovementAudio->Stop();
		MovementAudio->SetSound(MovmentStart);
		MovementAudio->Play();
	}
	
}

void AOfficeRobot::MoveToZap() {
	bItsZapTime = true;
	MoveTo(ERoboNavPoints::PlayerOfficeLeftFront);
}


void AOfficeRobot::PlayVoice(class USoundBase* Sound, FTimerDynamicDelegate Delegate) {
	if (!Sound) return;
	if (VoiceOutput->IsPlaying()) VoiceOutput->Stop();
	VoiceOutput->SetSound(Sound);
	VoiceOutput->Play();
	if (WaitTimer.IsValid()) GetWorld()->GetTimerManager().ClearTimer(WaitTimer);
	VoiceOutput->OnAudioFinished.Clear();
	VoiceOutput->OnAudioFinished.Add(Delegate);
}

void AOfficeRobot::Wait(float Time, FTimerDynamicDelegate Delegate) {
	if (WaitTimer.IsValid()) GetWorld()->GetTimerManager().ClearTimer(WaitTimer);
	VoiceOutput->OnAudioFinished.Clear();
	GetWorld()->GetTimerManager().SetTimer(WaitTimer, Delegate, Time, false);
}

void AOfficeRobot::StartTutorial() {
	OnStartTutorial();
}

void AOfficeRobot::Zap() {
	PostProcess->bUnbound = true;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AOfficeRobot::UnZap,1.0,false);
	UOfficeStatics::GetOfficeGameMode(this)->LossLife();
	OnZap();
}



void AOfficeRobot::UnZap() {
	PostProcess->bUnbound = false;
	if (UOfficeStatics::GetOfficeGameMode(this)->Lives <= 0) {
		UOfficeStatics::GetOffcieCharacter(this)->OnGameOver();
	}
}