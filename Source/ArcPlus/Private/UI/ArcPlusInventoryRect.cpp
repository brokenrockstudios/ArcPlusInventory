// Copyright 2025 Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#include "UI/ArcPlusInventoryRect.h"

FArcPlusInventoryRect::FArcPlusInventoryRect(): Box(FVector2D(0, 0), FVector2D(1, 1))
{
}

FArcPlusInventoryRect::FArcPlusInventoryRect(const FVector2D& InPosition, const FVector2D& InSize): Box(InPosition, InPosition + InSize)
{
}

int32 FArcPlusInventoryRect::Left() const
{
	return Box.Min.X;
}

int32 FArcPlusInventoryRect::Right() const
{
	return Box.Max.X;
}

int32 FArcPlusInventoryRect::Top() const
{
	return Box.Min.Y;
}

int32 FArcPlusInventoryRect::Bottom() const
{
	return Box.Max.Y;
}

FVector2D FArcPlusInventoryRect::GetPosition() const
{
	return Box.Min;
}

FVector2D FArcPlusInventoryRect::GetSize() const
{
	return Box.GetSize();
}

bool FArcPlusInventoryRect::HasPositiveArea() const
{
	return Box.GetArea() > 0;
}

bool FArcPlusInventoryRect::Overlaps(const FArcPlusInventoryRect& Other) const
{
	if (!HasPositiveArea() || !Other.HasPositiveArea())
	{
		return false;
	}
	return Left() < Other.Right() &&
		Right() > Other.Left() &&
		Top() < Other.Bottom() &&
		Bottom() > Other.Top();
}

bool FArcPlusInventoryRect::IsWithinBounds(const FVector2D& GridSize) const
{
	return Left() >= 0 &&
		Top() >= 0 &&
		Right() <= GridSize.X &&
		Bottom() <= GridSize.Y;
}

FString FArcPlusInventoryRect::ToString() const
{
	return FString::Printf(TEXT("Position: (%s), Size: (%s)"), *GetPosition().ToString(), *GetSize().ToString());
}
