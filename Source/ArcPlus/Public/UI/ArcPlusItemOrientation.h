// Copyright Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#pragma once

/**
 * 
 */
UENUM(BlueprintType)
enum class EArcPlusItemOrientation : uint8
{
	DefaultOrientation UMETA(DisplayName = "Default Rotation"),
	Rotated_90,
	Rotated_180,
	Rotated_270,

	ArcPlusItemOrientation_MAX UMETA(Hidden)
};
