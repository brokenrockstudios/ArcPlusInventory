// Copyright Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#include "ArcPlusWorldPlaceableItem.h"

AArcPlusWorldPlaceableItemBase::AArcPlusWorldPlaceableItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

AArcItemStackWorldObject* AArcPlusWorldPlaceableItemBase::SpawnWorldItem()
{
	return nullptr;
}

void AArcPlusWorldPlaceableItemBase::BeginPlay()
{
	Super::BeginPlay();
	if (SpawnBehavior == EArcPlusSpawnBehavior::RegisterWithWorldSpawner)
	{
		// if (UArcPlusWorldItemSpawnerSubsystem* worldSubsystem = UWorld::GetSubsystem<UArcPlusWorldItemSpawnerSubsystem>(GetWorld()))
		// {
		// 	worldSubsystem->RegisterWorldPlaceableItem(this);
		// }
	}
	if (SpawnBehavior == EArcPlusSpawnBehavior::SpawnOnBeginPlay) {
		SpawnWorldItem();
	}
}

void AArcPlusWorldPlaceableItemBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// if (SpawnBehavior == EArcPlusSpawnBehavior::RegisterWithWorldSpawner && UArcPlusWorldItemSpawnerSubsystem* worldSubsystem = UWorld::GetSubsystem<UArcPlusWorldItemSpawnerSubsystem>(GetWorld()))
	// {
	// 	worldSubsystem->UnregisterWorldPlaceableItem(this);
	// }
	Super::EndPlay(EndPlayReason);
}

