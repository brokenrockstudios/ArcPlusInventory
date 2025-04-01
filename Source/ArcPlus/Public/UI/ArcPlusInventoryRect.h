// Copyright 2025 Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "ArcPlusInventoryRect.generated.h"

// Define a structure to represent an item's position and size in the grid
USTRUCT()
struct ARCPLUSINVENTORY_API FArcPlusInventoryRect
{
	GENERATED_BODY()

	FBox2d Box;

	FArcPlusInventoryRect();
	FArcPlusInventoryRect(const FVector2D& InPosition, const FVector2D& InSize);

	int32 Left() const;
	int32 Right() const;
	int32 Top() const;
	int32 Bottom() const;

	FVector2D GetPosition() const;
	FVector2D GetSize() const;

	bool HasPositiveArea() const;
	bool Overlaps(const FArcPlusInventoryRect& Other) const;
	bool IsWithinBounds(const FVector2D& GridSize) const;
	FString ToString() const;
};
