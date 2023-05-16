// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Data : ModuleRules
{
	public Data(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"UMG",

			"Projects",
			"InputCore",
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
