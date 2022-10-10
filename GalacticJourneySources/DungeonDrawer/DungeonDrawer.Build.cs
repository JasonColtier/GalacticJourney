// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DungeonDrawer : ModuleRules
{
	public DungeonDrawer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","HeadMountedDisplay","GameplayTasks","UMG"
			// "AIModule","Networking"
			});
		
		// // Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// PrivateDependencyModuleNames.Add("GameplayTasks");
	}
}
