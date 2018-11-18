#pragma once

#include "OfficeEnums.generated.h"

UENUM()
enum class ERoboNavPoints : uint8 {
	Unknown = 0,
	PlayerOfficeLeftFront = 1,
	PlayerOfficeLeftBack = 2,
	PlayerOfficeRightFront = 3,
	PlayerOfficeRightBack = 4,
	LeftOfficeBack = 5,
	FrontOfficeBack = 6,
	FrontOfficeFront = 10,
	FrontCorridorEnd = 7,
	FarCorridorEnd = 8,
	FarCorridorCorner = 9,
};