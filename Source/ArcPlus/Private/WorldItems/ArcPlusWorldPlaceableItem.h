// Copyright Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/ArcItemStackWorldObject.h"
#include "ArcPlusWorldPlaceableItem.generated.h"

UENUM(BlueprintType)
enum class EArcPlusSpawnBehavior : uint8
{
	// Spawn the item on BeginPlay
	SpawnOnBeginPlay,
	// Register with WorldSpawner and allow it to spawn the item over a period of time
	RegisterWithWorldSpawner,
	// Do not spawn the item
	DoNotSpawn
};


UCLASS(Abstract)
class ARCPLUSINVENTORY_API AArcPlusWorldPlaceableItemBase : public AActor
{
	GENERATED_BODY()
public:

	AArcPlusWorldPlaceableItemBase();
	void BeginPlay();
	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	// Override this class with things for Item Generator or other mechanisms.
	UFUNCTION(BlueprintCallable, Category = "ArcPlus")
	virtual AArcItemStackWorldObject* SpawnWorldItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArcPlus")
	bool bEnabled = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ArcPlus")
	EArcPlusSpawnBehavior SpawnBehavior = EArcPlusSpawnBehavior::RegisterWithWorldSpawner;
};
