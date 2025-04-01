// Copyright Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.


#include "ArcPlusWorldPlaceableItem_Generator.h"

#include "ArcInventoryDeveloperSettings.h"
#include "ArcPlusInventory.h"
#include "Generators/ArcItemGenerator.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AArcPlusWorldPlaceableItem_Generator::AArcPlusWorldPlaceableItem_Generator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AArcItemStackWorldObject* AArcPlusWorldPlaceableItem_Generator::SpawnWorldItem()
{
	// Only server can spawn world items!
	if (GetLocalRole() != ROLE_Authority) {
		return nullptr;
	}

	if (IsValid(SpawnedItemStack)) {
		return SpawnedItemStack;
	}

	if (!IsValid(ItemGenerator)) {
		return nullptr;
	}

	const FTransform Transform = GetActorTransform();
	FArcItemGeneratorContext Context;
	// Context.UserObject = GetOwner();
	UArcItemStackBase* ItemStack = ItemGenerator->GenerateItemStack(Context);

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

