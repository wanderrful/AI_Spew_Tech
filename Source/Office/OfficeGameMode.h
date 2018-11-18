// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OfficeEnums.h"
#include "OfficeGameMode.generated.h"

UCLASS(minimalapi, config=enigne)
class AOfficeGameMode : public AGameModeBase
{
	GENERATED_BODY()

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void RegisterScreenWidget(class UOfficeScreen* Widget);

	UFUNCTION(BlueprintCallable)
	void RaportMousePosition(FVector2D Pos);

	FTimerHandle TimerHandle;


public:

	UPROPERTY()
	int32 Lives;

	UPROPERTY(BlueprintReadOnly)
	float Performance;

	UPROPERTY(BlueprintReadOnly)
	float TotalCounter;
	
	UFUNCTION(BlueprintCallable)
	void GoodAnwser();

	UFUNCTION(BlueprintCallable)
	void BadAnwser();

	UFUNCTION(BlueprintCallable)
	void DecreaseCounter();

	UFUNCTION(BlueprintCallable)
	void StartPerforamceDescrese();
	
	UFUNCTION()
	void GenerateCode();

	UFUNCTION()
	void DecodeCode();

	UFUNCTION()
	void LossLife();

	UPROPERTY()
	UOfficeScreen* Screen;

	UPROPERTY(config)
	TArray<float> DonTKnowWhatThisDo;

	UPROPERTY()
	TMap<ERoboNavPoints, class ARobotTargetPoint*> NavPoints;

	UPROPERTY()
	class AOfficeRobot* Robot;

	UPROPERTY()
	class AAIController* RobotAI;

	UPROPERTY(BlueprintReadWrite)
	bool bUnlockQuit;

	TArray<FString> DecodedBookCode;

	FString DecodedCode;

	AOfficeGameMode();
};



