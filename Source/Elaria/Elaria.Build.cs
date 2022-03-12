// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Elaria : ModuleRules
{
	public Elaria(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
