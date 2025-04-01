// Copyright Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#include "UI/ArcPlusBaseItemCardWidget.h"

#include "Modular/ArcItemStackModular.h"

UArcItemStackBase* UArcPlusBaseItemCardWidget::GetItemStack() const
{
	return ItemStack;
}

UArcItemStackModular* UArcPlusBaseItemCardWidget::GetItemStackModular() const
{
	return Cast<UArcItemStackModular>(ItemStack);
}

void UArcPlusBaseItemCardWidget::SetItemStack(UArcItemStackBase* InItemStack, const FArcInventoryItemSlotReference& InSlot)
{
	ItemStack = InItemStack;
	ItemSlot = InSlot;
	BP_OnItemStackSet(ItemStack, ItemSlot);
}
