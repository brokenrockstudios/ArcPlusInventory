// Copyright 2025 Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#include "ArcPlus/Public/UI/ArcPlusLibrary.h"

#include "ArcPlusGameplayTags.h"
#include "ArcPlus/Public/UI/ArcPlusInventoryRect.h"
#include "Modular/ArcItemStackModular.h"

// User-configurable bit allocations as compile-time constants
constexpr uint32 TAB_BITS = 8; // 8 bits = 256 possible tabs/pages
constexpr uint32 X_BITS = 8; // 8 bits = 256 possible X positions
constexpr uint32 Y_BITS = 8; // 8 bits = 256 possible Y positions
constexpr uint32 ROT_BITS = 2; // 2 bits = 4 possible rotation values (cardinal directions).  Most games typically only support 2 values (0 and 1)
constexpr uint32 UNUSED_BITS = 6; // 6 bits reserved for future use. Or reallocation into above as needed. 

// Calculate bit positions
constexpr uint32 TAB_SHIFT = 0;
constexpr uint32 X_SHIFT = TAB_SHIFT + TAB_BITS;
constexpr uint32 Y_SHIFT = X_SHIFT + X_BITS;
constexpr uint32 ROT_SHIFT = Y_SHIFT + Y_BITS;
constexpr uint32 UNUSED_SHIFT = ROT_SHIFT + ROT_BITS;

// Calculate masks
constexpr uint32 TAB_MASK = (1 << TAB_BITS) - 1;
constexpr uint32 X_MASK = (1 << X_BITS) - 1;
constexpr uint32 Y_MASK = (1 << Y_BITS) - 1;
constexpr uint32 ROT_MASK = (1 << ROT_BITS) - 1;
constexpr uint32 UNUSED_MASK = (1 << UNUSED_BITS) - 1;

// Compile-time check to ensure we don't exceed 32 bits
static_assert(TAB_BITS + X_BITS + Y_BITS + ROT_BITS + UNUSED_BITS <= 32, "Bit allocation exceeds 32 bits");

int32 UArcPlusLibrary::PackPosition(int32 Tab, int32 X, int32 Y, EArcPlusItemOrientation Rotation)
{
	uint32 packedValue = 0;
	constexpr uint32 unused = 0; // Reserved for future use. 
	packedValue |= (Tab & TAB_MASK) << TAB_SHIFT;
	packedValue |= (X & X_MASK) << X_SHIFT;
	packedValue |= (Y & Y_MASK) << Y_SHIFT;
	int32 RotationValue = static_cast<int32>(Rotation);
	packedValue |= (RotationValue & ROT_MASK) << ROT_SHIFT;
	packedValue |= (unused & UNUSED_MASK) << UNUSED_SHIFT;
	return packedValue;
}

void UArcPlusLibrary::UnpackPosition(int32 packedValue, int32& Tab, int32& X, int32& Y, int32& Rotation)
{
	Tab = (packedValue >> TAB_SHIFT) & TAB_MASK;
	X = (packedValue >> X_SHIFT) & X_MASK;
	Y = (packedValue >> Y_SHIFT) & Y_MASK;
	Rotation = (packedValue >> ROT_SHIFT) & ROT_MASK;
	// Unused = (packedValue >> UNUSED_SHIFT) & UNUSED_MASK;
}

int32 UArcPlusLibrary::GetTab(int32 packedValue)
{
	const uint32 uPackedValue = packedValue;
	return (uPackedValue >> TAB_SHIFT) & TAB_MASK;
}

int32 UArcPlusLibrary::GetX(int32 packedValue)
{
	const uint32 uPackedValue = packedValue;
	return (uPackedValue >> X_SHIFT) & X_MASK;
}

int32 UArcPlusLibrary::GetY(int32 packedValue)
{
	const uint32 uPackedValue = packedValue;
	return (uPackedValue >> Y_SHIFT) & Y_MASK;
}

int32 UArcPlusLibrary::GetRot(int32 packedValue)
{
	const uint32 uPackedValue = packedValue;
	return (uPackedValue >> ROT_SHIFT) & ROT_MASK;
}

int32 UArcPlusLibrary::GetUnused(int32 packedValue)
{
	const uint32 uPackedValue = packedValue;
	return (uPackedValue >> UNUSED_SHIFT) & UNUSED_MASK;
}

FArcPlusInventoryRect UArcPlusLibrary::MakeItemRectRef(const UArcItemStackModular* Item, const FArcInventoryItemSlotReference& Slot)
{
	static FArcPlusInventoryRect ZeroRect = FArcPlusInventoryRect(FVector2D::ZeroVector, FVector2D::ZeroVector);
	// More testing to see if this assumption is 'safe' or if there is a 'better' way of handling this?
	// if the Slot is invalid, we are likely doing a 'pick up' from ground type operation.
	// We technically still are doing a 'Swap' operation, but the source item is not in a slot.
	if (!IsValid(Slot))
	{
		// A size of 0,0, will always assume no overlaps with anything. And a valid 0,0 point.
		// This assumption makes other code easier to write.
		return ZeroRect;
	}

	// A non-modular item is always assumed to be 1x1
	FVector2D size = FVector2D::One();
	if (Item)
	{
		const int32 bRotation = UArcPlusLibrary::GetRot(Slot.GetSlotId());
		const int32 itemHeight = Item->GetStatTagStackCount(ArcPlusGameplayTags::Inventory_Item_Size_Height);
		const int32 itemWidth = Item->GetStatTagStackCount(ArcPlusGameplayTags::Inventory_Item_Size_Width);

		// horizontal
		if (bRotation % 2 == 0)
		{
			size = FVector2D(itemHeight, itemWidth);
		}
		else
		{
			size = FVector2D(itemWidth, itemHeight);
		}
	}
	const FVector2D position(
		UArcPlusLibrary::GetX(Slot.GetSlotId()),
		UArcPlusLibrary::GetY(Slot.GetSlotId())
	);

	return FArcPlusInventoryRect(position, size);
}

FArcPlusInventoryRect UArcPlusLibrary::MakeItemRect(const UArcItemStackModular* Item, const FArcInventoryItemSlot& Slot)
{
	const FVector2D position(UArcPlusLibrary::GetX(Slot.SlotId), UArcPlusLibrary::GetY(Slot.SlotId));

	// A non-modular item is always assumed to be 1x1
	FVector2D size = FVector2D::One();
	if (Item)
	{
		const int32 bRotation = UArcPlusLibrary::GetRot(Slot.SlotId);
		const int32 itemHeight = Item->GetStatTagStackCount(ArcPlusGameplayTags::Inventory_Item_Size_Height);
		const int32 itemWidth = Item->GetStatTagStackCount(ArcPlusGameplayTags::Inventory_Item_Size_Width);
		// horizontal
		if (bRotation % 2 == 0)
		{
			size = FVector2D(itemHeight, itemWidth);
		}
		else
		{
			size = FVector2D(itemWidth, itemHeight);
		}
	}

	return FArcPlusInventoryRect(position, size);
}
