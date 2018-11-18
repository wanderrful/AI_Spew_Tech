#include "UserWidget.h"
#include "OfficeScreen.generated.h"

UCLASS()
class UOfficeScreen : public UUserWidget {

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SummonIRC();
		
	UFUNCTION(BlueprintImplementableEvent)
	void ToggleDeadWeb();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMousePositionRaported(FVector2D Pos);
};