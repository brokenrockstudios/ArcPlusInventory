// Copyright Broken Rock Studios LLC. All Rights Reserved.

#include "RockArrayFunctionLibrary.h"

void URockArrayFunctionLibrary::ShuffleArray(TArray<UObject*> Array)
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

void URockArrayFunctionLibrary::ShuffleArrayWithSeed(TArray<UObject*>& Array, int32 InitialSeed)
{
	const FRandomStream RandomStream(InitialSeed);
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

void URockArrayFunctionLibrary::ShuffleArrayFromRandomStream(TArray<UObject*>& Array, const FRandomStream& RandomStream)
{
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
