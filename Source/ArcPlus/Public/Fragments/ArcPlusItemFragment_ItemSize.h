// Copyright Broken Rock Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modular/ArcItemFragment.h"
#include "ArcPlusItemFragment_ItemSize.generated.h"

/**
 * 
 */
UCLASS()
class ARCPLUSINVENTORY_API UArcPlusItemFragment_ItemSize : public UArcItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ArcPlus")
	FVector2D ItemSize;

	UFUNCTION(BlueprintCallable, Category = "ArcPlus")
	FVector2D GetItemSize() const;
};
