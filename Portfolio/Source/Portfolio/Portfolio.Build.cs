// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Portfolio : ModuleRules
{
	public Portfolio(ReadOnlyTargetRules Target) : base(Target)
	{
        
         // From my Plugin
         PrivateDependencyModuleNames.AddRange(new string[] { "ShowDamage" });
        PublicDependencyModuleNames.AddRange(new string[] { "ShowDamage" });

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "EnhancedInput",
            "NetCore",
            "UMG",

            "ShowDamage",
        });
		

		//GameplayAbilities
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
        });


        //AI
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "AIModule",
            "GameplayTasks",
            "NavigationSystem"
        });
    }
}
