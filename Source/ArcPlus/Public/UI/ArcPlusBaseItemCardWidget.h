// Copyright Broken Rock Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcInventoryItemTypes.h"
#include "CommonUserWidget.h"
#include "Modular/ArcInventoryComponent_Modular.h"

#include "ArcPlusBaseItemCardWidget.generated.h"

class UArcInventoryComponent_Modular;
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
	TObjectPtr<UArcItemStackBase> CurrentItemStack;

	UPROPERTY(BlueprintReadOnly, Category = "ArcPlus", Meta = (ExposeOnSpawn = true))
	FArcInventoryItemSlotReference CurrentItemSlot;



	// Consider moving 1 level up in a class?
	void BindNewInventory(UArcInventoryComponent_Modular* Inventory);
	
	UPROPERTY(EditAnywhere, Category="Inventory")
	FArcInventoryQuery ItemSlotQuery;
	void RebindSlot();
	UFUNCTION()
	void OnInventoryEvent(UArcInventoryComponent_Modular* Inventory, FGameplayTag Tag, const FArcInventoryModularEventPayload& Payload);
	
	UFUNCTION(BlueprintImplementableEvent, Category="Inventory", meta=(DisplayName="OnStatTagChanged"))
	void K2_OnStatTagChanged(UArcItemStackModular* ItemStack, FGameplayTag StatTag, int32 NewValue, int32 OldValue);
	void K2_OnStatTagChanged_Implementation(UArcItemStackModular* ItemStack, FGameplayTag StatTag, int32 NewValue, int32 OldValue) {}
	
	UFUNCTION()
	virtual void OnStatTagChanged(UArcItemStackModular* ItemStack, FGameplayTag StatTag, int32 NewValue, int32 OldValue);
	UFUNCTION()
	void OnItemSlotChanged( UArcInventoryComponent* Inventory, const FArcInventoryItemSlotReference& ItemSlotRef, UArcItemStackBase* ItemStack, UArcItemStackBase* PreviousItemStack, FGameplayTag ContextTag);

	UFUNCTION(BlueprintImplementableEvent, Category="Inventory", meta=(DisplayName="UpdateItem"))
	void K2_UpdateItem(UArcItemStackModular* itemStack);
	void K2_UpdateItem_Implementation(UArcItemStackModular* itemStack) {}
	
};
