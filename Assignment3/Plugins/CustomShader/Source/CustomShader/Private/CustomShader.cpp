// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CustomShader.h"
#include "Interfaces/IPluginManager.h"
#include "Logging/LogMacros.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "FCustomShaderModule"

void FCustomShaderModule::StartupModule()
{
	// Maps virtual shader source directory to the plugin's actual shaders directory.
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("CustomShader"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/Plugin"), PluginShaderDir);
}

void FCustomShaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomShaderModule, CustomShader)