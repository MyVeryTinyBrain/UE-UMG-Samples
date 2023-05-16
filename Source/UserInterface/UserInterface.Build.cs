// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UserInterface : ModuleRules
{
	public UserInterface(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Data", "NiagaraUIRenderer" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
