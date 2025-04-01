// Copyright Broken Rock Studios LLC. All Rights Reserved.


#include "ArcPlusWorldPlaceableItem_Static.h"

#include "ArcInventoryDeveloperSettings.h"
#include "ArcPlusInventory.h"
#include "Kismet/GameplayStatics.h"
#include "Modular/ArcInventoryModularBPFL.h"
#include "Modular/ArcItemStackModular.h"


// Sets default values
AArcPlusWorldPlaceableItem_Static::AArcPlusWorldPlaceableItem_Static()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AArcItemStackWorldObject* AArcPlusWorldPlaceableItem_Static::SpawnWorldItem()
{
	// Only server can spawn world items!
	if (GetLocalRole() != ROLE_Authority) {
		return nullptr;
	}

	// It's already spawned
	if (IsValid(SpawnedItemStack)) {
		return SpawnedItemStack;
	}

	// 
	if (!ItemDefinition) {
	 	return nullptr;
	 }

	const FTransform Transform = GetActorTransform();
	FArcItemGeneratorContext Context;
	// Context.UserObject = GetOwner();
	// TODO: What if we want to generate a non ModularItem?
	UArcItemStackBase* ItemStack = UArcInventoryModularBPFL::QuickGenerateModularItem(ItemDefinition, this);

	AArcItemStackWorldObject* StackObject = GetWorld()->SpawnActorDeferred<AArcItemStackWorldObject>(
		GetDefault<UArcInventoryDeveloperSettings>()->ItemStackWorldObjectClass, Transform);
	
	if (IsValid(StackObject)) {
		UGameplayStatics::FinishSpawningActor(StackObject, Transform);
		StackObject->SetItemStack(ItemStack);
		SpawnedItemStack = StackObject;
		return StackObject;
	}
	else 
	{
		UE_LOG(LogArcPlus, Warning, TEXT("Failed to spawn item stack world object"));
	}

	return nullptr;
}

// Called when the game starts or when spawned
void AArcPlusWorldPlaceableItem_Static::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArcPlusWorldPlaceableItem_Static::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

