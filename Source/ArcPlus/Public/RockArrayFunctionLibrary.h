// Copyright Broken Rock Studios LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RockArrayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ARCPLUSINVENTORY_API URockArrayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// shuffle an arbitrary TArray
	UFUNCTION(BlueprintCallable, Category = "Rock|Array")
	static void ShuffleArray(TArray<UObject*> Array);
	UFUNCTION(BlueprintCallable, Category = "Rock|Array")
	static void ShuffleArrayWithSeed(TArray<UObject*>& Array, int32 InitialSeed);
	UFUNCTION(BlueprintCallable, Category = "Rock|Array")
	static void ShuffleArrayFromRandomStream(TArray<UObject*>& Array, const FRandomStream& RandomStream);	
	
	template <typename T>
	static void ShuffleArray_Generic(TArray<T>& Array)
	{
		FRandomStream RandomStream;
		RandomStream.GenerateNewSeed();
		const int32 LastIndex = Array.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			const int32 Index = RandomStream.RandRange(i, LastIndex);
			if (i != Index)
			{
				Array.SwapMemory(i, Index);
			}
		}
	}
	
};
