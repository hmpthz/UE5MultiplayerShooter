// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MultiplayerShooterEditorTarget : TargetRules
{
    public MultiplayerShooterEditorTarget( TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange( new string[] { "MultiplayerShooter" } );
    }
}
