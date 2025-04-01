// Copyright Broken Rock Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcPlusWorldPlaceableItem.h"
#include "ArcPlusWorldPlaceableItem_Static.generated.h"

class UArcItemFragment;

UCLASS()
class ARCPLUSINVENTORY_API AArcPlusWorldPlaceableItem_Static : public AArcPlusWorldPlaceableItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArcPlusWorldPlaceableItem_Static();

	virtual AArcItemStackWorldObject* SpawnWorldItem() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Definition")
	TObjectPtr<UArcInventoryModularItemDef> ItemDefinition;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "ArcPlus|Item")
	TObjectPtr<AArcItemStackWorldObject> SpawnedItemStack;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
