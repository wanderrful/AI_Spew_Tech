#include "GameFramework/Character.h"
#include "OfficeEnums.h"
#include "OfficeRobot.generated.h"

UCLASS()
class AOfficeRobot : public ACharacter {

	GENERATED_BODY()
public: 

	AOfficeRobot();

	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveTo(ERoboNavPoints Destination);

	UPROPERTY(EditAnywhere)
	class UAudioComponent* VoiceOutput;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* MovementAudio;

	UPROPERTY(EditAnywhere)
	USoundBase* MovmentStart;

	UPROPERTY(EditAnywhere)
	USoundBase* MovmentEnd;

	UPROPERTY(EditAnywhere)
	class UPostProcessComponent* PostProcess;

	FTimerHandle WaitTimer;

	UPROPERTY(BlueprintReadOnly)
	ERoboNavPoints CurrentDestination;

	UPROPERTY(BlueprintReadOnly)
	ERoboNavPoints PreviuesPosition;

	UPROPERTY(BlueprintReadOnly)
	ERoboNavPoints CurrentPosition;

	UPROPERTY(BlueprintReadOnly)
	bool bOnTheMove;

	UPROPERTY(BlueprintReadWrite)
	bool bItsZapTime;

	UFUNCTION(BlueprintCallable)
	void PlayVoice(class USoundBase* Sound, FTimerDynamicDelegate Delegate);

	UFUNCTION(BlueprintCallable)
	void PlayVoiceWithoutDelegate(class USoundBase* Sound);

	UFUNCTION(BlueprintCallable, Category = "Office Game")
	void Wait(float Time, FTimerDynamicDelegate Delegate);

	UFUNCTION(BlueprintCallable, Category = "Office Game")
	void StartTutorial();

	UFUNCTION(BlueprintImplementableEvent, Category = "Office Game")
	void OnStartTutorial();

	UFUNCTION(BlueprintCallable, Category = "Office Game")
	void Zap();
	void UnZap();

	UFUNCTION(BlueprintImplementableEvent, Category = "Office Game")
	void OnZap();

	UFUNCTION(BlueprintCallable, Category = "Office Game")
	void MoveToZap();

	UFUNCTION(BlueprintImplementableEvent, Category = "Office Game")
	void OnAboutToZap();

};