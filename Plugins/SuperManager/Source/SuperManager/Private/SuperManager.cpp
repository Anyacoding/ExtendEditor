// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperManager.h"

#include "ContentBrowserModule.h"
#include "DebugHeader.h"
#include "EditorAssetLibrary.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "SlateWidgets/AdvanceDeletionWidget.h"

#define LOCTEXT_NAMESPACE "FSuperManagerModule"

void FSuperManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	InitContentBrowserExtention();
	RegisterAdvanceDeletionTab();
}

void FSuperManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FName("AdvanceDeletion"));
}

#pragma region ContentBrowserMenuExtention

void FSuperManagerModule::InitContentBrowserExtention()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	TArray<FContentBrowserMenuExtender_SelectedPaths>& ContentBrowserModuleMenuExtenders = ContentBrowserModule.GetAllPathViewContextMenuExtenders();

	FContentBrowserMenuExtender_SelectedPaths CustomCBMenuDelegate;
	CustomCBMenuDelegate.BindRaw(this, &FSuperManagerModule::CustomContentBrowserExtender);
	
	ContentBrowserModuleMenuExtenders.Add(CustomCBMenuDelegate);
}

TSharedRef<FExtender> FSuperManagerModule::CustomContentBrowserExtender(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> MenuExtender(new FExtender());
	
	if (SelectedPaths.Num() > 0)
	{
		MenuExtender->AddMenuExtension(FName("Delete"), EExtensionHook::After, nullptr, FMenuExtensionDelegate::CreateRaw(this, &FSuperManagerModule::AddContentBrowserEntry));
		this->FolderPathsSelected = SelectedPaths;
	}
	
	return MenuExtender;
}

void FSuperManagerModule::AddContentBrowserEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("Delete Unused Assets")), FText::FromString(TEXT("Safely delete all unused assets under folder")), FSlateIcon(), FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnDeleteUnusedAssetButtonClicked));
	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("Delete Empty Folders")), FText::FromString(TEXT("Safely delete all empty folders")), FSlateIcon(), FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnDeleteEmptyFolderButtonClicked));
	MenuBuilder.AddMenuEntry(FText::FromString(TEXT("Advance Deletion")), FText::FromString(TEXT("List assets by specific condition in a tab for deleting")), FSlateIcon(), FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnAdvanceDeletionButtonClicked));
}

void FSuperManagerModule::OnDeleteUnusedAssetButtonClicked()
{
	if (FolderPathsSelected.Num() > 1)
	{
		DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("You can only do this to one folder."));
		return;
	}

	FixUpRedirectors();

	TArray<FString> AssetPathNames = UEditorAssetLibrary::ListAssets(FolderPathsSelected[0]);

	if (AssetPathNames.Num() == 0)
	{
		DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("No asset found under selected folder."), false);
		return;
	}

	EAppReturnType::Type ConfirmResult = DebugHeader::ShowMsgDialog(EAppMsgType::YesNo, TEXT("A total of ") + FString::FromInt(AssetPathNames.Num()) + TEXT(" found.\nWould you like to procceed?"));

	if (ConfirmResult == EAppReturnType::No) return;
	
	TArray<FAssetData> UnusedAssetDatas;

	for (const FString& AssetPathName : AssetPathNames)
	{
		// Don't touch root folder
		if (AssetPathName.Contains(TEXT("Developers")) || AssetPathName.Contains(TEXT("Collections")) ||
		    AssetPathName.Contains(TEXT("__ExternalActors__")) || AssetPathName.Contains(TEXT("__ExternalObjects__")))
		{
			continue;
		}

		if (UEditorAssetLibrary::DoesAssetExist(AssetPathName) == false) continue;

		DebugHeader::Print(AssetPathName);

		TArray<FString> AssetReferencers = UEditorAssetLibrary::FindPackageReferencersForAsset(AssetPathName);

		if (AssetReferencers.Num() == 0)
		{
			const FAssetData UnusedAssetData = UEditorAssetLibrary::FindAssetData(AssetPathName);
			UnusedAssetDatas.Add(UnusedAssetData);
		}
	}

	if (UnusedAssetDatas.Num() > 0)
	{
		int32 NumOfAssetsDeleted = ObjectTools::DeleteAssets(UnusedAssetDatas);
	}
	else
	{
		DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("No unused asset found under selected folder."), false);
	}
}

void FSuperManagerModule::OnDeleteEmptyFolderButtonClicked()
{
	if (FolderPathsSelected.Num() > 1)
	{
		DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("You can only do this to one folder."));
		return;
	}
	
	FixUpRedirectors();
	
	TArray<FString> FolderPathsArray = UEditorAssetLibrary::ListAssets(FolderPathsSelected[0], true, true);
	uint32 Counter = 0;

	FString EmptyFolderPathsNames;
	TArray<FString> EmptyFolderPathsArray;

	for (const FString& FolderPath : FolderPathsArray)
	{
		// Don't touch root folder
		if (FolderPath.Contains(TEXT("Developers")) || FolderPath.Contains(TEXT("Collections")) ||
			FolderPath.Contains(TEXT("__ExternalActors__")) || FolderPath.Contains(TEXT("__ExternalObjects__")))
		{
			continue;
		}

		if (UEditorAssetLibrary::DoesDirectoryExist(FolderPath) == false) continue;

		if (UEditorAssetLibrary::DoesDirectoryHaveAssets(FolderPath) == false)
		{
			EmptyFolderPathsNames.Append(FolderPath);
			EmptyFolderPathsNames.Append(TEXT("\n"));
			EmptyFolderPathsArray.Add(FolderPath);
		}
	}

	if (EmptyFolderPathsArray.Num() == 0)
	{
		DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("No empty folder found under selected folder."), false);
		return;
	}

	EAppReturnType::Type ConfirmResult = DebugHeader::ShowMsgDialog(EAppMsgType::OkCancel, TEXT("Empty folder found in:\n") + EmptyFolderPathsNames + TEXT("\nWould you like to delete all?"), false);

	if (ConfirmResult == EAppReturnType::Cancel) return;

	for (const FString& EmptyFolderPath : EmptyFolderPathsArray)
	{
		UEditorAssetLibrary::DeleteDirectory(EmptyFolderPath)
		? ++Counter
		: (DebugHeader::Print(TEXT("Failed to delete ") + EmptyFolderPath, FColor::Red), 1);
	}

	if (Counter > 0)
	{
		DebugHeader::ShowNotifyInfo(TEXT("Successfully deleted ") + FString::FromInt(Counter) + TEXT(" empty folders"));
	}
}

void FSuperManagerModule::OnAdvanceDeletionButtonClicked()
{
	FixUpRedirectors();
	FGlobalTabmanager::Get()->TryInvokeTab(FName("AdvanceDeletion"));
}

void FSuperManagerModule::FixUpRedirectors()
{
	TArray<UObjectRedirector*> RedirectorsToFixArray;
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	FARFilter Filter;
	Filter.bRecursivePaths = true;
	Filter.PackagePaths.Emplace("/Game");
	Filter.ClassPaths.Emplace(UObjectRedirector::StaticClass()->GetClassPathName());

	TArray<FAssetData> OutRedirectors;
	AssetRegistryModule.Get().GetAssets(Filter, OutRedirectors);
	
	for(const FAssetData& RedirectorData : OutRedirectors)
	{
		if(UObjectRedirector* RedirectorToFix = Cast<UObjectRedirector>(RedirectorData.GetAsset()))
		{
			RedirectorsToFixArray.Add(RedirectorToFix);
		}
	}

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	AssetToolsModule.Get().FixupReferencers(RedirectorsToFixArray);
}

#pragma endregion


#pragma region CustomEditorTab

void FSuperManagerModule::RegisterAdvanceDeletionTab()
{
	FGlobalTabmanager::Get()->RegisterTabSpawner(FName("AdvanceDeletion"), FOnSpawnTab::CreateRaw(this, &FSuperManagerModule::OnSpawnAdvanceDeletionTab))
	.SetDisplayName(FText::FromString(TEXT("Advance Deletion")));
}

TSharedRef<SDockTab> FSuperManagerModule::OnSpawnAdvanceDeletionTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return
	SNew(SDockTab).TabRole(ETabRole::NomadTab)
	[
		SNew(SAdvanceDeletionTab)
		.AssetDatasToStore(GetAllAssetDataUnderSelectedFolder())
		.CurrentSelectedFolder(FolderPathsSelected[0])
	];
}

TArray<TSharedPtr<FAssetData>> FSuperManagerModule::GetAllAssetDataUnderSelectedFolder()
{
	if (FolderPathsSelected.Num() > 1)
	{
		DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("You can only do this to one folder."));
		return {};
	}

	FixUpRedirectors();
	
	TArray<TSharedPtr<FAssetData>> AvailableAssetData;
	TArray<FString> AssetPathNames = UEditorAssetLibrary::ListAssets(FolderPathsSelected[0]);

	for (const FString& AssetPathName : AssetPathNames)
	{
		// Don't touch root folder
		if (AssetPathName.Contains(TEXT("Developers")) || AssetPathName.Contains(TEXT("Collections")) ||
			AssetPathName.Contains(TEXT("__ExternalActors__")) || AssetPathName.Contains(TEXT("__ExternalObjects__")))
		{
			continue;
		}

		if (UEditorAssetLibrary::DoesAssetExist(AssetPathName) == false) continue;

		const FAssetData Data = UEditorAssetLibrary::FindAssetData(AssetPathName);

		AvailableAssetData.Add(MakeShared<FAssetData>(Data));
	}

	return AvailableAssetData;
}

#pragma endregion


#pragma region ProccessDataForAdvanceDeletionTab

bool FSuperManagerModule::DeleteSingleAssetForAssetList(const FAssetData& AssetDataToDelete)
{
	FixUpRedirectors();
	return (ObjectTools::DeleteAssets({AssetDataToDelete}) > 0);
}

bool FSuperManagerModule::DeleteMultipleAssetsForAssetList(const TArray<FAssetData>& AssetDatasToDelete)
{
	FixUpRedirectors();
	return (ObjectTools::DeleteAssets(AssetDatasToDelete) > 0);
}

void FSuperManagerModule::ListUnusedAssetsForAssetList(const TArray<TSharedPtr<FAssetData>>& AssetDataToFilter, TArray<TSharedPtr<FAssetData>>& OutUnusedAssetDatas)
{
	OutUnusedAssetDatas.Empty();
	
	for (const TSharedPtr<FAssetData> DataSharedPtr : AssetDataToFilter)
	{
		TArray<FString> AssetReferencers = 
		UEditorAssetLibrary::FindPackageReferencersForAsset(DataSharedPtr->GetObjectPathString());

		if (AssetReferencers.Num() == 0)
		{
			OutUnusedAssetDatas.Add(DataSharedPtr);
		}
	}
}

void FSuperManagerModule::ListSameNameAssetsForAssetList(const TArray<TSharedPtr<FAssetData>>& AssetDataToFilter, TArray<TSharedPtr<FAssetData>>& OutUnusedAssetDatas)
{
	OutUnusedAssetDatas.Empty();

	TMultiMap<FString, TSharedPtr<FAssetData>> AssetInfoMap;
	
	for (const TSharedPtr<FAssetData>& DataSharedPtr : AssetDataToFilter)
	{
		AssetInfoMap.Emplace(DataSharedPtr->AssetName.ToString(), DataSharedPtr);
	}

	for (const TSharedPtr<FAssetData>& DataSharedPtr : AssetDataToFilter)
	{
		TArray<TSharedPtr<FAssetData>> OutAssetData;
		AssetInfoMap.MultiFind(DataSharedPtr->AssetName.ToString(), OutAssetData);

		if (OutAssetData.Num() <= 1) continue;

		for (const TSharedPtr<FAssetData>& SameNameData : OutAssetData)
		{
			if (SameNameData.IsValid())
			{
				OutUnusedAssetDatas.AddUnique(SameNameData);
			}
		}
	}
}

void FSuperManagerModule::SyncContentBrowserToClickedAssetsForAssetList(const FString& AssetPathToSync)
{
	const TArray<FString> AssetsPathToSync{AssetPathToSync};
	UEditorAssetLibrary::SyncBrowserToObjects(AssetsPathToSync);
}

#pragma endregion


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSuperManagerModule, SuperManager)