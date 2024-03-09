// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSuperManagerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
#pragma region ContentBrowserMenuExtention
	
	void InitContentBrowserExtention();

	TSharedRef<FExtender> CustomContentBrowserExtender(const TArray<FString>& SelectedPaths);
	
#pragma endregion 
};
