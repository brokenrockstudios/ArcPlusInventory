// Copyright 2025 Broken Rock Studios LLC. All Rights Reserved.
// See the LICENSE file for details.

#include "ArcPlusInventory.h"

#define LOCTEXT_NAMESPACE "FArcPlusModule"

DEFINE_LOG_CATEGORY(LogArcPlus);

void FArcPlusInventoryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FArcPlusInventoryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FArcPlusInventoryModule, ArcPlusInventory)