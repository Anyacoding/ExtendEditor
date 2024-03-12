// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/QuickMaterialCreationWidget.h"

#include "DebugHeader.h"
#include "EditorAssetLibrary.h"
#include "EditorUtilityLibrary.h"

#pragma region QuickMaterialCreationCore

void UQuickMaterialCreationWidget::CreateMaterialFromSelectedTextures()
{
	if (bCustomMaterialName)
	{
		if (MaterialName.IsEmpty() || MaterialName.Equals(TEXT("M_")))
		{
			DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("Please enter a valid name."));
			return;
		}
	}

	TArray<FAssetData> SelectedAssetDatas = UEditorUtilityLibrary::GetSelectedAssetData();
	TArray<UTexture2D*> SelectedTextures;
	FString SelectedTextureFolderPath;

	if (ProcessSelectionData(SelectedAssetDatas, SelectedTextures, SelectedTextureFolderPath) == false) return;

	if (ChekcIsNameUsed(SelectedTextureFolderPath, MaterialName)) return;
	
	DebugHeader::Print(SelectedTextureFolderPath);
}

#pragma endregion

#pragma region QuickMaterialCreation

// Process the selected data, will filter out textures, and return false if non-texture selected
bool UQuickMaterialCreationWidget::ProcessSelectionData(const TArray<FAssetData>& SelectedDataToProcess, TArray<UTexture2D*>& OutSelectedTextures, FString& OutSelectedPackagePath)
{
	if (SelectedDataToProcess.Num() == 0)
	{
		DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("No texture selected."));
		return false;
	}

	bool bMaterialNameSet = false;

	for (const FAssetData& SelectedData : SelectedDataToProcess)
	{
		UObject* SelectedAsset = SelectedData.GetAsset();

		if (SelectedAsset == nullptr) continue;

		UTexture2D* SelectedTexture = Cast<UTexture2D>(SelectedAsset);

		if (SelectedTexture == nullptr)
		{
			DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("Please select only texture\n") + SelectedAsset->GetName() + TEXT(" is not a texture."));
			return false;
		}

		OutSelectedTextures.Add(SelectedTexture);

		if (OutSelectedPackagePath.IsEmpty())
		{
			OutSelectedPackagePath = SelectedData.PackagePath.ToString();
		}

		if (bCustomMaterialName == false && bMaterialNameSet == false)
		{
			MaterialName = SelectedAsset->GetName();
			MaterialName.RemoveFromStart(TEXT("T_"));
			MaterialName.InsertAt(0, TEXT("M_"));
			bMaterialNameSet = true;
		}
	}

	return true;
}

bool UQuickMaterialCreationWidget::ChekcIsNameUsed(const FString& FolderPathToCheck, const FString& MaterialNameToCheck)
{
	TArray<FString> ExistingAssetPaths = UEditorAssetLibrary::ListAssets(FolderPathToCheck, false);

	for (const FString& ExistingAssetPath : ExistingAssetPaths)
	{
		const FString ExistingAssetName = FPaths::GetBaseFilename(ExistingAssetPath);

		if (ExistingAssetName.Equals(MaterialNameToCheck))
		{
			DebugHeader::ShowMsgDialog(EAppMsgType::Ok, MaterialNameToCheck + TEXT(" is already used by asset."));
			return true;
		}
	}

	return false;
}

#pragma endregion
