// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArcPlusInventory : ModuleRules
{
	public ArcPlusInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"ArcInventory",
				"GameplayTags",
				"GameplayAbilities",
				"CoreUObject",
				"Engine",
				"InputCore",
				"CommonUI",
				"UMG"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate",
				"SlateCore",
				"NetCore",
			}
		);
	}
}