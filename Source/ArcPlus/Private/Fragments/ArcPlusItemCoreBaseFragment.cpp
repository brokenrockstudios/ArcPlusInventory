// Copyright 2025 Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#include "Fragments/ArcPlusItemCoreBaseFragment.h"

#include "Modular/ArcInventoryModularItemDef.h"

#define LOCTEXT_NAMESPACE "ArcPlus"

UArcPlusItemCoreBaseFragment::UArcPlusItemCoreBaseFragment()
	: ItemName(LOCTEXT("DefaultItemName", "Default Item Name"))
	  , ItemDescription(LOCTEXT("DefaultItemDescription", "Item Description"))
	  , ItemDescriptionShort(LOCTEXT("DefaultItemDescriptionShort", " Short Item Description"))
{
}

FText UArcPlusItemCoreBaseFragment::GetDisplayName() const
{
	return ItemName;
}

FText UArcPlusItemCoreBaseFragment::GetItemDescription() const
{
	return ItemDescription;
}

FText UArcPlusItemCoreBaseFragment::GetItemDescriptionShort() const
{
	return ItemDescriptionShort;
}

UArcPlusItemCoreBaseFragment* UArcPlusItemCoreBaseFragment::GetFromItemDef(const UArcInventoryModularItemDef* ItemDef)
{
	// If the item doesn't have this fragment. Could we return a proxy fake default valued item instead?
	UArcPlusItemCoreBaseFragment* Fragment = ItemDef->FindFirstFragment<UArcPlusItemCoreBaseFragment>();
	return Fragment;
}

#undef LOCTEXT_NAMESPACE
