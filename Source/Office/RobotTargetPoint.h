#include "Engine/TargetPoint.h"
#include "OfficeEnums.h"
#include "RobotTargetPoint.generated.h"

UCLASS()
class ARobotTargetPoint : public ATargetPoint {

	GENERATED_BODY()

	ARobotTargetPoint();

public:
	UPROPERTY(EditAnywhere, Category = "Robot Navigation")
	ERoboNavPoints PointAssigned;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Box;

	virtual void BeginPlay() override;

};