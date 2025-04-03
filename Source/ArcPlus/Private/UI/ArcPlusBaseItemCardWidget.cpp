// Copyright Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#include "UI/ArcPlusBaseItemCardWidget.h"

#include "ArcInventory.h"
#include "ArcItemBPFunctionLibrary.h"
#include "Modular/ArcInventoryComponent_Modular.h"
#include "Modular/ArcItemStackModular.h"

UArcItemStackBase* UArcPlusBaseItemCardWidget::GetItemStack() const
{
	return CurrentItemStack;
}

UArcItemStackModular* UArcPlusBaseItemCardWidget::GetItemStackModular() const
{
	return Cast<UArcItemStackModular>(CurrentItemStack);
}

void UArcPlusBaseItemCardWidget::SetItemStack(UArcItemStackBase* InItemStack, const FArcInventoryItemSlotReference& InSlot)
{
	CurrentItemStack = InItemStack;
	CurrentItemSlot = InSlot;
	BP_OnItemStackSet(CurrentItemStack, CurrentItemSlot);
}

void UArcPlusBaseItemCardWidget::BindNewInventory(UArcInventoryComponent_Modular* Inventory)
{
	if (!Inventory)
	{
		return;
	}
	// Do we need to unbind somewhere? 
	Inventory->OnItemSlotChange.AddDynamic(this, &UArcPlusBaseItemCardWidget::OnItemSlotChanged);
	Inventory->GetModularInventoryEventForTag(FArcInvEventActivateTag).AddUObject(this, &UArcPlusBaseItemCardWidget::OnInventoryEvent);
	Inventory->GetModularInventoryEventForTag(FArcInvEventDeactivateTag).AddUObject(this, &UArcPlusBaseItemCardWidget::OnInventoryEvent);
	
	RebindSlot();
}

void UArcPlusBaseItemCardWidget::RebindSlot()
{
	if (!ItemSlotQuery.IsValid())
	{
		return;
	}
	// TODO: What if it's not an inventory belonging to the player, but some other inventory?
	UArcInventoryComponent_Modular* modularInventory = UArcItemBPFunctionLibrary::GetModularInventory(GetOwningPlayerPawn(), false);

	if (!modularInventory)
	{
		return;
	}
	CurrentItemSlot= modularInventory->Query_GetFirstSlot(ItemSlotQuery);
}

void UArcPlusBaseItemCardWidget::OnInventoryEvent(
	UArcInventoryComponent_Modular* Inventory, FGameplayTag Tag, const FArcInventoryModularEventPayload& Payload)
{
	if (IsValid(CurrentItemSlot) && CurrentItemSlot == Payload.ItemSlot)
	{
		// Payload.ItemStack = CurrentItemStack;
		if (Tag.MatchesTagExact(FArcInvEventActivateTag))
		{
			// ActivateEvent(inventory, payload);
		}
		if (Tag.MatchesTagExact(FArcInvEventDeactivateTag))
		{
			// DeactivateEvent(inventory, payload);
		}
	}
}

void UArcPlusBaseItemCardWidget::OnStatTagChanged(UArcItemStackModular* ItemStack, FGameplayTag Stat, int32 NewValue, int32 OldValue)
{
	K2_OnStatTagChanged(ItemStack, Stat, NewValue, OldValue);
}

void UArcPlusBaseItemCardWidget::OnItemSlotChanged(
	UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStackBase* ItemStack,
	UArcItemStackBase* PreviousItemStack, FGameplayTag ContextTag)
{
	if (!Inventory)
	{
		return;
	}
	// Make sure we are looking at the correct item slot corresponding to the event
	if (IsValid(CurrentItemSlot) && CurrentItemSlot == ItemSlotRef)
	{
		UArcItemStackModular* NewItemStack = Cast<UArcItemStackModular>(ItemStack);
		UArcItemStackModular* LastItemStack = Cast<UArcItemStackModular>(CurrentItemStack);

		if (NewItemStack != LastItemStack)
		{
			if (LastItemStack)
			{
				LastItemStack->OnStatTagChanged.RemoveDynamic(this, &UArcPlusBaseItemCardWidget::OnStatTagChanged);
			}

			if (NewItemStack)
			{
				NewItemStack->OnStatTagChanged.AddDynamic(this, &UArcPlusBaseItemCardWidget::OnStatTagChanged);
			}
		}
		if (ItemStack != CurrentItemStack)
		{
			CurrentItemStack = NewItemStack;
		}

		K2_UpdateItem(NewItemStack);
	}
}
