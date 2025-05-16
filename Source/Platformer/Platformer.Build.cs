// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Platformer : ModuleRules
{
	public Platformer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
