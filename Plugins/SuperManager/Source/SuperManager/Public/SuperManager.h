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

	TArray<FString> FolderPathsSelected;
	
	void InitContentBrowserExtention();

	TSharedRef<FExtender> CustomContentBrowserExtender(const TArray<FString>& SelectedPaths);

	void AddContentBrowserEntry(FMenuBuilder& MenuBuilder);

	void OnDeleteUnusedAssetButtonClicked();

	void OnDeleteEmptyFolderButtonClicked();

	void OnAdvanceDeletionButtonClicked();

	void FixUpRedirectors();

#pragma endregion

private:
#pragma region CustomEditorTab

	void RegisterAdvanceDeletionTab();

	TSharedRef<SDockTab> OnSpawnAdvanceDeletionTab(const FSpawnTabArgs& SpawnTabArgs);

	TArray<TSharedPtr<FAssetData>> GetAllAssetDataUnderSelectedFolder();
	
#pragma endregion

public:
#pragma region ProccessDataForAdvanceDeletionTab

	bool DeleteSingleAssetForAssetList(const FAssetData& AssetDataToDelete);
	
#pragma endregion
	
};
