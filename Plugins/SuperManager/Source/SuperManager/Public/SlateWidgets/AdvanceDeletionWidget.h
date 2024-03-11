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

	TArray<TSharedPtr<FAssetData>> DisplayAssetDatas;

	TArray<TSharedPtr<FAssetData>> AssetDatasToDelete;
	
	TArray<TSharedRef<SCheckBox>> CheckBoxes;

	TArray<TSharedPtr<FString>> ComboBoxSourceItems;

	TSharedPtr<STextBlock> ComboDisplayTextBlock;

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
	

#pragma region ComboBoxForListingCondition

	TSharedRef<SComboBox<TSharedPtr<FString>>> ConstructComboBox();

	TSharedRef<SWidget> OnGenerateComboContent(TSharedPtr<FString> SourceItem);

	void OnComboSelectionChanged(TSharedPtr<FString> SelectedOption, ESelectInfo::Type InSelectInfo);
	
#pragma endregion

	
	void RefreshAssetListView();
	
	static FSlateFontInfo GetEmbossedTextTextFont()
	{
		return FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	}
};