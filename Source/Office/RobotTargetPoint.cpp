#include "RobotTargetPoint.h"
#include "OfficeStatics.h"
#include "OfficeGameMode.h"
#include "Components/BoxComponent.h"

ARobotTargetPoint::ARobotTargetPoint() {
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	Box->SetBoxExtent(FVector(10.0, 10.0, 500.0));
	Box->SetupAttachment(RootComponent);

}

void ARobotTargetPoint::BeginPlay() {
	Super::BeginPlay();
	AOfficeGameMode* GM = UOfficeStatics::GetOfficeGameMode(this);
	if (!GM->NavPoints.Contains(PointAssigned)) {
		GM->NavPoints.Add(PointAssigned, this);
	}
	else UE_LOG(LogTemp, Error, TEXT("Dupilcate nav point: %s"), *GetName());
}