// Copyright Broken Rock Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldItemSpawnerSubsystem.generated.h"

class AArcPlusWorldPlaceableItemBase;


// RespawnItemOnTimer 

// struct to contain PlaceableItem but also if it's been used yet
USTRUCT()
struct FWorldPlaceableItem
{
	GENERATED_BODY()
	UPROPERTY()
	TObjectPtr<AArcPlusWorldPlaceableItemBase> WorldPlaceableItem;
	UPROPERTY()
	bool bHasBeenUsed = false;
};

/**
* Take all PlaceableItem actors in the world and spawn their items
* But spread them out over time so we don't spawn them all at once on the same frame
* We want to spread them out over a few frames so we don't cause a hitch
 */
UCLASS()
class ARCPLUSINVENTORY_API UArcPlusWorldItemSpawnerSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;

	void RegisterWorldPlaceableItem(AArcPlusWorldPlaceableItemBase* WorldPlaceableItem);
	void UnregisterWorldPlaceableItem(AArcPlusWorldPlaceableItemBase* WorldPlaceableItem);

	// Anything can register a point, but only the server can spawn items
	//void RegisterWorldPlaceablePoint(FVector WorldPlaceablePoint);

	// ~Begin FTickableGameObject
	virtual TStatId GetStatId() const override;
	virtual bool IsTickableWhenPaused() const override;

	// ~End FTickableGameObject interface


	//UFUNCTION(BlueprintCallable, Category = "WorldItemSpawnerSubsystem")
	//void BeginSpawningWorldItems();

	// UFUNCTION(BlueprintCallable, Category = "WorldItemSpawnerSubsystem")
	// void EnqueueWorldItemSpawn(UArcItemGenerator* ItemGenerator, FVector Location, FRotator Rotation);
	UFUNCTION(BlueprintCallable, Category = "WorldItemSpawnerSubsystem")
	void SpawnWorldItem();

	UFUNCTION(BlueprintCallable, Category = "WorldItemSpawnerSubsystem")
	void Reset();

	FTimerHandle SpawnTimerHandle;

	// Override via config
	UPROPERTY()
	int32 MaxItemsToSpawn = 30;
	UPROPERTY()
	int32 ItemsToSpawnPerFrame = 1;
	UPROPERTY()
	float TimeBetweenSpawns = 1 / 30.0f;
	// overrideable via cvar
	UPROPERTY(meta=(Units="seconds"))
	float TimeBeforeFirstSpawn = 1.0f;

	UPROPERTY()
	int32 ItemsSpawned = 0;
	UPROPERTY()
	float TimeSinceLastSpawn = 0.0f;
	UPROPERTY()
	float TimeSinceStart = 0.0f;

	/**
	 * 
	 */
	UPROPERTY()
	TArray<TObjectPtr<AArcPlusWorldPlaceableItemBase>> WorldPlaceableItems;
	UPROPERTY()
	TArray<TObjectPtr<AArcPlusWorldPlaceableItemBase>> OriginalWorldPlaceableItems;

	UPROPERTY()
	TArray<FVector> WorldPlaceablePoints;
};


// We could also do this in a more deterministic way by having a list of items to spawn and a time to spawn them

//
// enum class EArcPlusActorSpawnerAuthority : uint8_t
// {
// 	ServerAuthoritative = 0,
// 	ClientAuthoritative = 1,
// 	ERockActorSpawnerAuthority_MAX = 2
// };
//
//

// Inspiration from UEFN's ItemSpawnerDevice Documentation

// ItemSpawnerDevice
// RespawnRule = [Off, Instant, Delayed 
// RandomSpawns [ Off, Random, NoRepeats(No repeats until all have been used)
// BaseVisibleToPlayer
// InitialSpawnItemDelay (
// TimeBeforeFirstSpawn, [Never, Instant, 15 Seconds, Pick An Amount of Time]+
// TimeBetweenSpawns, [Never, Instant, 15 Seconds, Pick An Amount of Time]+
// InitialWeaponAmmo, [None, Full, Pick An Amount of Ammo]+
// AllowSpawningWhenBlocked [True, False] (If the player is standing on it)
// InitialMovementOfITem [ None (Fixed), Gravity, OnGround, Toss]
// Should Toss be vertically up, or in a random direction?
// EnabledAtGameStart = [True, False]
