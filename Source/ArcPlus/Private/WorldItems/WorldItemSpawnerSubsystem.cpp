// Copyright Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#include "WorldItems/WorldItemSpawnerSubsystem.h"

#include "ArcPlusWorldPlaceableItem.h"
#include "RockArrayFunctionLibrary.h"

static TAutoConsoleVariable<int32> CVarMaxItemsToSpawn(
	TEXT("ItemSpawner.MaxItemsToSpawn"),
	100,
	TEXT("Controls how many items to spawn"),
	ECVF_Default);
static TAutoConsoleVariable<float> CVarTimeBeforeFirstSpawn(
	TEXT("ItemSpawner.TimeBeforeFirstSpawn"),
	1.0f,
	TEXT("Controls how long to wait before spawning the first item"),
	ECVF_Default);

void UArcPlusWorldItemSpawnerSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	TimeBeforeFirstSpawn = CVarTimeBeforeFirstSpawn.GetValueOnGameThread();
	MaxItemsToSpawn = CVarMaxItemsToSpawn.GetValueOnGameThread();
}

void UArcPlusWorldItemSpawnerSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ItemsSpawned >= MaxItemsToSpawn)
	{
		SetTickableTickType(ETickableTickType::Never);
		return;
	}
	// If we are only spawning a subset of the total items, shuffle the array. So it's not the same items every time.
	if (WorldPlaceableItems.Num() == 0)
	{
		WorldPlaceableItems = OriginalWorldPlaceableItems;
		URockArrayFunctionLibrary::ShuffleArray(TArray<UObject*>(WorldPlaceableItems));
	}
	if (TimeSinceStart < TimeBeforeFirstSpawn)
	{
		TimeSinceStart += DeltaTime;
		return;
	}
	TimeSinceLastSpawn += DeltaTime;
	if (TimeSinceLastSpawn <= TimeBetweenSpawns)
	{
		return;
	}
	TimeSinceLastSpawn = 0;
	for (int i = 0; i < ItemsToSpawnPerFrame; i++)
	{
		ItemsSpawned++;
		SpawnWorldItem();
	}
}

void UArcPlusWorldItemSpawnerSubsystem::RegisterWorldPlaceableItem(AArcPlusWorldPlaceableItemBase* WorldPlaceableItem)
{
	WorldPlaceableItems.Add(WorldPlaceableItem);
}

void UArcPlusWorldItemSpawnerSubsystem::UnregisterWorldPlaceableItem(AArcPlusWorldPlaceableItemBase* WorldPlaceableItem)
{
	WorldPlaceableItems.Remove(WorldPlaceableItem);
}

TStatId UArcPlusWorldItemSpawnerSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UWorldItemSpawnerSubsystem, STATGROUP_Tickables);
}

bool UArcPlusWorldItemSpawnerSubsystem::IsTickableWhenPaused() const
{
	return true;
}

inline void UArcPlusWorldItemSpawnerSubsystem::SpawnWorldItem()
{
	// remove from the array and spawn
	if (WorldPlaceableItems.Num() == 0)
	{
		return;
	}
	AArcPlusWorldPlaceableItemBase* WorldPlaceableItem = WorldPlaceableItems.Pop();
	if (WorldPlaceableItem && WorldPlaceableItem->bEnabled)
	{
		WorldPlaceableItem->SpawnWorldItem();
	}
}

void UArcPlusWorldItemSpawnerSubsystem::Reset()
{
	ItemsSpawned = 0;
	SetTickableTickType(GetTickableTickType());
}

//
// void UWorldItemSpawnerSubsystem::RegisterWorldPlaceablePoint(FVector WorldPlaceablePoint)
// {
// 	
// }
//
// void UWorldItemSpawnerSubsystem::EnqueueWorldItemSpawn(UArcItemGenerator* ItemGenerator, FVector Location, FRotator Rotation)
// {
// 	
// }
//
// AArcItemStackWorldObject* UWorldItemSpawnerSubsystem::SpawnWorldItem()
// {
// 	// // Only server can spawn world items!
// 	// if (GetLocalRole() != ROLE_Authority) {
// 	// 	return nullptr;
// 	// }
// 	//
// 	// if (IsValid(SpawnedItemStack)) {
// 	// 	return SpawnedItemStack;
// 	// }
// 	//
// 	//
// 	// if (!IsValid(ItemGenerator)) {
// 	// 	return nullptr;
// 	// }
// 	//
// 	// FTransform Transform = GetActorTransform();
// 	// FArcItemGeneratorContext Context;
// 	// UArcItemStackBase* ItemStack = ItemGenerator->GenerateItemStack(Context);
// 	//
// 	// AArcItemStackWorldObject* StackObject = GetWorld()->SpawnActorDeferred<AArcItemStackWorldObject>(
// 	// 	GetDefault<UArcInventoryDeveloperSettings>()->ItemStackWorldObjectClass, Transform);
// 	//
// 	// if (IsValid(StackObject)) {
// 	// 	UGameplayStatics::FinishSpawningActor(StackObject, Transform);
// 	// 	StackObject->SetItemStack(ItemStack);
// 	// 	SpawnedItemStack = StackObject;
// 	// 	return StackObject;
// 	// }
// 	// else {
// 	// 	UE_LOG(LogTemp, Warning, TEXT("Failed to spawn item stack world object"));
// 	// }
//
// 	// Since IsValid of this failed up above. Perhaps this should be nullptr instead?
// 	// return SpawnedItemStack;
// 	// BRS custom change
// 	return nullptr;
// }
