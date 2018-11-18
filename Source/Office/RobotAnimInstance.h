#include "Animation/AnimInstance.h"
#include "RobotAnimInstance.generated.h"

UCLASS()
class URobotAnimInstance : public UAnimInstance {

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldExtendArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldRetractArm;

};