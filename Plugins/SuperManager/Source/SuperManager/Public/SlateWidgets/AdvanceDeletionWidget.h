// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SAdvanceDeletionTab : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SAdvanceDeletionTab)
	{}

	SLATE_ARGUMENT(TArray<TSharedPtr<FAssetData>>, AssetDatasToStore)
	
	SLATE_END_ARGS()

private:
	TArray<TSharedPtr<FAssetData>> StoredAssetDatas;

	TSharedPtr<SListView<TSharedPtr<FAssetData>>> ConstructedAssetListView;

public:
	void Construct(const FArguments& InArgs);

private:
#pragma region RowWidgetForAssetListView

	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FAssetData> AssetDataToDisplay, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedRef<SCheckBox> ConstructCheckBox(const TSharedPtr<FAssetData>& AssetDataToDisplay);

	TSharedRef<STextBlock> ConstructTextForRowWidget(const FString& TextContent, const FSlateFontInfo& FontInfo);

	TSharedRef<SButton> ConstructButtonForRowWidget(const TSharedPtr<FAssetData>& AssetDataToDisplay);

	FReply OnDeleteButtonClicked(TSharedPtr<FAssetData> ClickedAssetData);

	void OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> AssetData);
	
#pragma endregion 
	
	TSharedRef<SListView<TSharedPtr<FAssetData>>> ConstructAssetListView();

	void RefreshAssetListView() const;
	
	static FSlateFontInfo GetEmbossedTextTextFont()
	{
		return FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	}
};