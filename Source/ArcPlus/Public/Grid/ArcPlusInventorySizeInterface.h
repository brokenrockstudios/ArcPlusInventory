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
 * 
 */
class ARCPLUSINVENTORY_API IArcPlusInventorySizeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual FVector2D GetItemSize() const;
	
};
