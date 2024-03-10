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

public:
	void Construct(const FArguments& InArgs);

private:
	TArray<TSharedPtr<FAssetData>> StoredAssetDatas;

	TArray<TSharedPtr<FAssetData>> AssetDatasToDelete;

	TSharedPtr<SListView<TSharedPtr<FAssetData>>> ConstructedAssetListView;

private:
#pragma region RowWidgetForAssetListView

	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FAssetData> AssetDataToDisplay, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedRef<SCheckBox> ConstructCheckBox(const TSharedPtr<FAssetData>& AssetDataToDisplay);

	TSharedRef<STextBlock> ConstructTextForRowWidget(const FString& TextContent, const FSlateFontInfo& FontInfo);

	TSharedRef<SButton> ConstructButtonForRowWidget(const TSharedPtr<FAssetData>& AssetDataToDisplay);

	FReply OnDeleteButtonClicked(TSharedPtr<FAssetData> ClickedAssetData);

	void OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> AssetData);
	
#pragma endregion

#pragma region TabButtons
	
	TSharedRef<SListView<TSharedPtr<FAssetData>>> ConstructAssetListView();
	
	TSharedRef<SButton> ConstructDeleteAllButton();
	TSharedRef<SButton> ConstructSelectAllButton();
	TSharedRef<SButton> ConstructDeSelectAllButton();

	FReply OnDeleteAllButtonClicked();
	FReply OnSelectAllButtonClicked();
	FReply OnDeSelectAllButtonClicked();

	TSharedRef<STextBlock> ConstructTextForTabButtons(const FString& TextContent);

#pragma endregion 
	
	void RefreshAssetListView() const;
	
	static FSlateFontInfo GetEmbossedTextTextFont()
	{
		return FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	}
};