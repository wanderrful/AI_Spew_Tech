#include "AIController.h"
#include "RobotAIController.generated.h"

UCLASS()
class ARobotAIController : public AAIController {

	GENERATED_BODY()

	class AOfficeRobot* Robot;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result) override;
	virtual void Possess(APawn * InPawn) override;

};