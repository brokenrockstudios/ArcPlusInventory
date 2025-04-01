// Copyright 2025 Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace ArcPlusGameplayTags
{
	ARCPLUSINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Action_SwappableCheck);

	ARCPLUSINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Item_Size_Height);
	ARCPLUSINVENTORY_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Inventory_Item_Size_Width);
}

// --- Standard Item Rarities
// Inventory.Item.Rarity.Common
// Inventory.Item.Rarity.Uncommon
// Inventory.Item.Rarity.Rare
// Inventory.Item.Rarity.Epic
// Inventory.Item.Rarity.Legendary
// Inventory.Item.Rarity.Mythic

// --- Special Item Rarities
// Inventory.Item.Rarity.Unique
// Inventory.Item.Rarity.Exotic
// Grey, no functional game value. Generally pointless item, maybe worth money?   
// Inventory.Item.Rarity.Trash

// Inventory.Item.Rarity.Custom // Fallback to secondary method


// --- Quest Item Rarities
// Inventory.Item.Rarity.Quest
// Inventory.Item.Rarity.Artifact
// Inventory.Item.Rarity.Cursed

// --- Developer Item Rarities
// hidden and should not be seen by players
// Inventory.Item.Rarity.Developer



// --- Unused Item Rarities, brainstorming
// Inventory.Item.Rarity.Relic or Ancient?
// Any real difference between these?
// Inventory.Item.Rarity.Broken
// Inventory.Item.Rarity.Damaged
// Inventory.Item.Rarity.Worn

// Possibly add
// Would look up in a DataTable or asset somewhere? Configurable but how?
// FLinearColor GetColorForRarity(EItemRarity Rarity);
// FText GetDisplayNameForRarity(EItemRarity Rarity);
// UTexture2D* GetIconForRarity(EItemRarity Rarity);