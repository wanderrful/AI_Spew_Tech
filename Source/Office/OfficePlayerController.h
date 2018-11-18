#include "GameFramework/PlayerController.h" 
#include "OfficePlayerController.generated.h"

UCLASS()
class AOfficePlayerController : public APlayerController {

	GENERATED_BODY()

	virtual FString ConsoleCommand(const FString& Command, bool bWriteToLog) override;

	virtual void BeginPlay();

};