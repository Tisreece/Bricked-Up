// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;

public class BrickedUp : ModuleRules
{
	public BrickedUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Slate",
			"SlateCore",
			"ApplicationCore",
			"UMG",
			"EnhancedInput",
			"Chaos",
			"ChaosSolverEngine",
			"GeometryCollectionEngine",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"OnlineSubsystem",
			"OnlineSubsystemSteam",
			"Steamworks",
			"OnlineSubsystemUtils"
		});

		// Steam Include Path
		// string SteamPath = Path.Combine(ModuleDirectory, "../ThirdParty/Steamworks/Steamv161/sdk/public");
		// PublicIncludePaths.Add(SteamPath);

		// string SteamLibPath = Path.Combine(ModuleDirectory, "../ThirdParty/Steamworks/Steamv161/sdk/redistributable_bin");
		// PublicAdditionalLibraries.Add(Path.Combine(SteamLibPath, "steam_api.lib"));

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
