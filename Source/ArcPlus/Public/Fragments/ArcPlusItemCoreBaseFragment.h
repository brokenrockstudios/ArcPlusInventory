// Copyright Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "ArcInventoryItemTypes.h"
#include "Modular/ArcItemFragment.h"

#include "ArcPlusItemCoreBaseFragment.generated.h"
class UArcInventoryModularItemDef;


/**
 * Core common base fragment for all game items
 */
UCLASS()
class ARCPLUSINVENTORY_API UArcPlusItemCoreBaseFragment : public UArcItemFragment
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "ArcPlus")
	FText ItemName;
	UPROPERTY(EditDefaultsOnly, Category = "ArcPlus")
	FText ItemDescription;
	UPROPERTY(EditDefaultsOnly, Category = "ArcPlus")
	FText ItemDescriptionShort;

public:
	UArcPlusItemCoreBaseFragment();

	UFUNCTION(BlueprintCallable, Category = "ArcPlus")
	FText GetDisplayName() const;
	UFUNCTION(BlueprintCallable, Category = "ArcPlus")
	FText GetItemDescription() const;
	UFUNCTION(BlueprintCallable, Category = "ArcPlus")
	FText GetItemDescriptionShort() const;

	static UArcPlusItemCoreBaseFragment* GetFromItemDef(const UArcInventoryModularItemDef* ItemDef);
};
