// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RTS : ModuleRules
{
	public RTS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"NavigationSystem",
			"AIModule",
			"GameplayTasks",
			"Paper2D"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			"RTS",
			"RTS/Public",
			"RTS/Public/Player",
			"RTS/Public/Units"
		});
	}
}