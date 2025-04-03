// Copyright 2025 Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#include "ArcPlus/Public/UI/ArcPlusLibrary.h"

#include "ArcPlusGameplayTags.h"
#include "ArcPlus/Public/UI/ArcPlusInventoryRect.h"
#include "Fragments/ArcPlusItemFragment_ItemSize.h"
#include "Grid/ArcPlusInventorySizeInterface.h"
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

int32 UArcPlusLibrary::PackPosition(int32 Tab, int32 X, int32 Y, EArcPlusItemOrientation Orientation)
{
	uint32 packedValue = 0;
	constexpr uint32 unused = 0; // Reserved for future use. 
	packedValue |= (Tab & TAB_MASK) << TAB_SHIFT;
	packedValue |= (X & X_MASK) << X_SHIFT;
	packedValue |= (Y & Y_MASK) << Y_SHIFT;
	const int32 RotationValue = static_cast<int32>(Orientation);
	packedValue |= (RotationValue & ROT_MASK) << ROT_SHIFT;
	packedValue |= (unused & UNUSED_MASK) << UNUSED_SHIFT;
	return packedValue;
}

void UArcPlusLibrary::UnpackPosition(int32 packedValue, int32& Tab, int32& X, int32& Y, EArcPlusItemOrientation& Orientation)
{
	Tab = GetTab(packedValue);
	X = GetX(packedValue);
	Y = GetY(packedValue);
	Orientation = GetOrientation(packedValue);
	// Unused = (packedValue >> UNUSED_SHIFT) & UNUSED_MASK;
}

int32 UArcPlusLibrary::GetTab(int32 packedValue)
{
	const uint32 uPackedValue = packedValue;
	return (uPackedValue >> TAB_SHIFT) & TAB_MASK;
}

FVector2D UArcPlusLibrary::GetPosition(int32 packedValue)
{
	return FVector2D(
		GetX(packedValue),
		GetY(packedValue)
	);
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

EArcPlusItemOrientation UArcPlusLibrary::GetOrientation(int32 packedValue)
{
	const uint32 uPackedValue = packedValue;
	return static_cast<EArcPlusItemOrientation>(uPackedValue >> ROT_SHIFT & ROT_MASK);
}

int32 UArcPlusLibrary::GetUnused(int32 packedValue)
{
	const uint32 uPackedValue = packedValue;
	return (uPackedValue >> UNUSED_SHIFT) & UNUSED_MASK;
}

FArcPlusInventoryRect UArcPlusLibrary::MakeItemRectRef(const UArcItemStackBase* Item, const FArcInventoryItemSlotReference& Slot)
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

	FVector2D size = UArcPlusLibrary::GetItemSize(Item);
	const EArcPlusItemOrientation bOrientation = UArcPlusLibrary::GetOrientation(Slot.GetSlotId());
	if (bOrientation == EArcPlusItemOrientation::DefaultOrientation || bOrientation == EArcPlusItemOrientation::Rotated_180)
	{
		size = FVector2D(size.X, size.Y);
	}
	else
	{
		size = FVector2D(size.Y, size.X);
	}
	const FVector2D position = GetPosition(Slot.GetSlotId());
	return FArcPlusInventoryRect(position, size);
}

FArcPlusInventoryRect UArcPlusLibrary::MakeItemRect(const UArcItemStackBase* Item, const FArcInventoryItemSlot& Slot)
{
	const EArcPlusItemOrientation bOrientation = UArcPlusLibrary::GetOrientation(Slot.SlotId);

	FVector2D size = UArcPlusLibrary::GetItemSize(Item);
	if (bOrientation == EArcPlusItemOrientation::DefaultOrientation || bOrientation == EArcPlusItemOrientation::Rotated_180)
	{
		size = FVector2D(size.X, size.Y);
	}
	else
	{
		size = FVector2D(size.Y, size.X);
	}
	const FVector2D position = GetPosition(Slot.SlotId);
	return FArcPlusInventoryRect(position, size);
}


FVector2D UArcPlusLibrary::GetItemSize(const UArcItemStackBase* Item)
{
	if (!Item)
	{
		return FVector2D::ZeroVector;
	}
	if (const IArcPlusInventorySizeInterface* InventoryInterface = Cast<IArcPlusInventorySizeInterface>(Item))
	{
		// HotPath A+. It's in your core item definition itself. Use this for most efficient lookup. 
		return InventoryInterface->GetItemSize();
	}
	else if (const UArcItemStackModular* ModularItem = Cast<UArcItemStackModular>(Item))
	{
		if (ModularItem->HasStatTag(ArcPlusGameplayTags::Inventory_Item_Size_Height))
		{
			const int32 itemHeight = ModularItem->GetStatTagStackCount(ArcPlusGameplayTags::Inventory_Item_Size_Height);
			const int32 itemWidth = ModularItem->GetStatTagStackCount(ArcPlusGameplayTags::Inventory_Item_Size_Width);
			return FVector2D(itemHeight, itemWidth);
		}
		else if (const UArcPlusItemFragment_ItemSize* ItemSizeFragment = Cast<UArcPlusItemFragment_ItemSize>(
			ModularItem->FindFirstFragment<UArcPlusItemFragment_ItemSize>()))
		{
			// HotPath B-. Fragments have extra 'iteration' time. Worst hot path.
			return ItemSizeFragment->GetItemSize();
		}
	}
	// return 1x1 for non modular item
	return FVector2D::One();
}
