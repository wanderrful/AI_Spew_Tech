#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class AInteractable : public AActor {

	GENERATED_BODY()

public:

	AInteractable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Hitbox;

	UPROPERTY(EditAnywhere, Category = "Office Game")
	FText DisplayText;

	UPROPERTY(EditAnywhere)
	bool bCanPickup;

	UFUNCTION(BlueprintPure, Category = "Office Game")
	virtual FText GetDisplayText();

	UFUNCTION(BlueprintPure, Category = "Office Game")
	virtual bool CanPickup();

	UFUNCTION(BlueprintImplementableEvent, Category = "Office Game")
	void OnUse();

	UFUNCTION(BlueprintImplementableEvent, Category = "Office Game")
	void OnPickUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "Office Game")
	void OnDrop();

};