#include "Kismet/BlueprintFunctionLibrary.h"
#include "OfficeEnums.h"
#include "OfficeStatics.generated.h"

UCLASS()
class UOfficeStatics : public UBlueprintFunctionLibrary {

	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Office")
	static AOfficeGameMode* GetOfficeGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Office")
	static FString GenerateRandomString();

	UFUNCTION(BlueprintPure, Category = "Office")
	static FString FloatToSting(float Float);

	UFUNCTION(BlueprintCallable, Category = "Office")
	static void ClearKeyboardFocus();

	UFUNCTION(BlueprintPure, Category = "Office")
	static FString GetSystemUsername();

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Office")
	static void RobotGoTo(const UObject* WorldContextObject, ERoboNavPoints Destination);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Office")
	static void RobotPlayVoice(const UObject* WorldContextObject, class USoundBase* Sound, FTimerDynamicDelegate Delegate);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Office")
	static void RobotWait(const UObject* WorldContextObject, float Time, FTimerDynamicDelegate Delegate);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Office")
	static class AOfficeCharacter* GetOffcieCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Office")
	static AOfficeRobot* GetRobot(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Office")
	static AAIController* GetRobotAI(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Office")
	static FString GetWhiteSpaceCode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = "Office")
	static FString GeBookCode(int32 ID, const UObject* WorldContextObject);


};