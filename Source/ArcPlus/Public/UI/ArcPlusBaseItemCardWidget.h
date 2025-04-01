// Copyright Broken Rock Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcInventoryItemTypes.h"
#include "CommonUserWidget.h"

#include "ArcPlusBaseItemCardWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ARCPLUSINVENTORY_API UArcPlusBaseItemCardWidget : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "ArcPlus")
	virtual UArcItemStackBase* GetItemStack() const;
	
	UFUNCTION(BlueprintPure, Category = "ArcPlus")
	virtual UArcItemStackModular* GetItemStackModular() const;

	UFUNCTION(BlueprintCallable, Category="ArcPlus")
	virtual void SetItemStack(UArcItemStackBase* InItemStack, const FArcInventoryItemSlotReference& InSlot);
	
	UFUNCTION(BlueprintImplementableEvent, Category="ArcPlus")
	void BP_OnItemStackSet(UArcItemStackBase* NewItemStack, const FArcInventoryItemSlotReference& InSlot);

protected:
	UPROPERTY(BlueprintReadOnly, Category="ArcPlus", BlueprintGetter=GetItemStack, Meta=(ExposeOnSpawn = true))
	TObjectPtr<UArcItemStackBase> ItemStack;

	UPROPERTY(BlueprintReadOnly, Category = "ArcPlus", Meta = (ExposeOnSpawn = true))
	FArcInventoryItemSlotReference ItemSlot;
};
