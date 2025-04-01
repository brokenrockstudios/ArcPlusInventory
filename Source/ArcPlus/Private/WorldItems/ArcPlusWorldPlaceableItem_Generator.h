// Copyright Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "ArcPlusWorldPlaceableItem.h"
#include "ArcPlusWorldPlaceableItem_Generator.generated.h"

UCLASS()
class ARCPLUSINVENTORY_API AArcPlusWorldPlaceableItem_Generator : public AArcPlusWorldPlaceableItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArcPlusWorldPlaceableItem_Generator();
	
	UPROPERTY(EditAnywhere, Category = "ArcPlus|Item", Instanced)
	TObjectPtr<class UArcItemGenerator> ItemGenerator;

	virtual AArcItemStackWorldObject* SpawnWorldItem() override;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "ArcPlus|Item")
	TObjectPtr<AArcItemStackWorldObject> SpawnedItemStack;

};
