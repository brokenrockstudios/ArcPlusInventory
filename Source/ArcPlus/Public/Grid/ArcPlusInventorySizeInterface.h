// Copyright Broken Rock Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ArcPlusInventorySizeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UArcPlusInventorySizeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Add this to your item class to provide a more performant lookup for item size.
 * Perhaps by implementing a cached size fragment lookup.  
 */
class ARCPLUSINVENTORY_API IArcPlusInventorySizeInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual FVector2D GetItemSize() const { return FVector2D::One(); }
};
