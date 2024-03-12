// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomStyle/SuperManagerStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

FName FSuperManagerStyle::StyleSetName = FName("SuperManagerStyle");
TSharedPtr<FSlateStyleSet> FSuperManagerStyle::CreatedSlateStyleSet = nullptr;

void FSuperManagerStyle::InitializedIcons()
{
	if (CreatedSlateStyleSet.IsValid() == false)
	{
		CreatedSlateStyleSet = CreateSlateStyleSet();
		FSlateStyleRegistry::RegisterSlateStyle(*CreatedSlateStyleSet);
	}
}

void FSuperManagerStyle::ShutDown()
{
	if (CreatedSlateStyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*CreatedSlateStyleSet);
		CreatedSlateStyleSet.Reset();
	}
}

TSharedRef<FSlateStyleSet> FSuperManagerStyle::CreateSlateStyleSet()
{
	TSharedRef<FSlateStyleSet> CustomStyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	const FString IconDir = IPluginManager::Get().FindPlugin(TEXT("SuperManager"))->GetBaseDir() + TEXT("/Resources");
	

	const FVector2d Icon16x16(16.0f, 16.0f);
	
	CustomStyleSet->SetContentRoot(IconDir);

	const FString DeleteUnusedAssetsIconPath = IconDir/"DeleteUnusedAsset.png";
	CustomStyleSet->Set("ContentBrowser.DeleteUnusedAssets", new FSlateImageBrush(DeleteUnusedAssetsIconPath, Icon16x16));

	const FString DeleteEmptyFoldersIconPath = IconDir/"DeleteEmptyFolders.png";
	CustomStyleSet->Set("ContentBrowser.DeleteEmptyFolders", new FSlateImageBrush(DeleteEmptyFoldersIconPath, Icon16x16));

	const FString AdvanceDeletionIconPath = IconDir/"AdvanceDeletion.png";
	CustomStyleSet->Set("ContentBrowser.AdvanceDeletion", new FSlateImageBrush(AdvanceDeletionIconPath, Icon16x16));
	
	return CustomStyleSet;
}
