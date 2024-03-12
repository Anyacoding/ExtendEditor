// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWidgets/AdvanceDeletionWidget.h"
#include "DebugHeader.h"
#include "SuperManager.h"

const FString& ListAll = TEXT("List All Available Assets");
const FString& ListUnused = TEXT("List Unused Assets");
const FString& ListSameName = TEXT("List Assets With Same Name");

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAdvanceDeletionTab::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;
	
	StoredAssetDatas = InArgs._AssetDatasToStore;
	DisplayAssetDatas = StoredAssetDatas;

	CheckBoxes.Empty();
	AssetDatasToDelete.Empty();
	ComboBoxSourceItems.Empty();
	
	ComboBoxSourceItems.Add(MakeShared<FString>(ListAll));
	ComboBoxSourceItems.Add(MakeShared<FString>(ListUnused));
	ComboBoxSourceItems.Add(MakeShared<FString>(ListSameName));

	FSlateFontInfo TitleTextFont = GetEmbossedTextTextFont();
	TitleTextFont.Size = 30;
	
	ChildSlot
	[
		// Main VerticalBox
		SNew(SVerticalBox)
		// First vertical box slot for title text
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Advance Deletion")))
			.Font(TitleTextFont)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::White)
		]
		// Second slot for drop down to specify the listing condition
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(3.0f)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				ConstructComboBox()
			]
			// Help text for combo box slot 
			+SHorizontalBox::Slot()
			.FillWidth(0.6f)
			[
				ConstructComboHelpTexts(TEXT("Specify the listing condition in the drop. Left mouse click to go to where asset is located"), ETextJustify::Center)
			]
			// Help text for folder path
			+SHorizontalBox::Slot()
			.FillWidth(0.6f)
			[
				ConstructComboHelpTexts(TEXT("Current Folder:\n") + InArgs._CurrentSelectedFolder, ETextJustify::Right)
			]
		]
		// Third slot for the asset list
		+SVerticalBox::Slot()
		.VAlign(VAlign_Fill)
		[
			SNew(SScrollBox)
			+SScrollBox::Slot()
			[
				ConstructAssetListView()
			]
		]
		// Fourth slot for 3 buttons
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			// DeleteAllButton slot
			+SHorizontalBox::Slot()
			.FillWidth(10.0f)
			.Padding(5.0f)
			[
				ConstructDeleteAllButton()
			]
			// SelectAllButton slot
			+SHorizontalBox::Slot()
			.FillWidth(10.0f)
			.Padding(5.0f)
			[
				ConstructSelectAllButton()
			]
			// DeSelectAllButton slot
			+SHorizontalBox::Slot()
			.FillWidth(10.0f)
			.Padding(5.0f)
			[
				ConstructDeSelectAllButton()
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION


#pragma region RowWidgetForAssetListView

TSharedRef<ITableRow>
SAdvanceDeletionTab::OnGenerateRowForList(TSharedPtr<FAssetData> AssetDataToDisplay, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (AssetDataToDisplay.IsValid() == false)
	{
		return SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable);
	}
	
	const FString DisplayAssetClassName = AssetDataToDisplay->GetClass()->GetName();
	const FString DisplayAssetName = AssetDataToDisplay->AssetName.ToString();

	FSlateFontInfo AssetClassNameFont = GetEmbossedTextTextFont();
	AssetClassNameFont.Size = 10;

	FSlateFontInfo AssetNameFont = GetEmbossedTextTextFont();
	AssetNameFont.Size = 10;
	
	TSharedRef<STableRow<TSharedPtr<FAssetData>>> ListViewWidget = 
	SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable)
	.Padding(FMargin(3.0f))
	[
		SNew(SHorizontalBox)
		// First slot for check box
		+SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.FillWidth(0.1f)
		[
			ConstructCheckBox(AssetDataToDisplay)
		]
		// Second slot for displaying asset class name
		+SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.FillWidth(0.5f)
		[
			ConstructTextForRowWidget(DisplayAssetClassName, AssetClassNameFont)
		]
		// Third slot for displaying asset name
		+SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			ConstructTextForRowWidget(DisplayAssetName, AssetNameFont)
		]
		// Fourth slot for a button
		+SHorizontalBox::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Fill)
		.Padding(0.0f, 0.0f, 5.0f, 0.0f)
		[
			ConstructButtonForRowWidget(AssetDataToDisplay)
		]
	];

	return ListViewWidget;
}

TSharedRef<SCheckBox> SAdvanceDeletionTab::ConstructCheckBox(const TSharedPtr<FAssetData>& AssetDataToDisplay)
{
	TSharedRef<SCheckBox> ConstructedCheckBox = 
	SNew(SCheckBox)
	.Type(ESlateCheckBoxType::CheckBox)
	.OnCheckStateChanged(this, &SAdvanceDeletionTab::OnCheckBoxStateChanged, AssetDataToDisplay)
	.Visibility(EVisibility::Visible);

	CheckBoxes.Add(ConstructedCheckBox);

	return ConstructedCheckBox;
}

void SAdvanceDeletionTab::OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> AssetData)
{
	switch (NewState)
	{
	case ECheckBoxState::Checked:
		DebugHeader::Print(TEXT("Checked"), FColor::Green);
		AssetDatasToDelete.AddUnique(AssetData);
		break;
	case ECheckBoxState::Unchecked:
		DebugHeader::Print(TEXT("Unchecked"), FColor::Red);
		if (AssetDatasToDelete.Contains(AssetData))
		{
			AssetDatasToDelete.Remove(AssetData);
		}
		break;
	case ECheckBoxState::Undetermined:
		DebugHeader::Print(TEXT("Undetermined"), FColor::Yellow);
		break;
	default:
		break;
	}
}

TSharedRef<STextBlock>
SAdvanceDeletionTab::ConstructTextForRowWidget(const FString& TextContent, const FSlateFontInfo& FontInfo)
{
	TSharedRef<STextBlock> ConstructedTextBlock = 
	SNew(STextBlock)
	.Text(FText::FromString(TextContent))
	.Font(FontInfo)
	.ColorAndOpacity(FColor::White);
	
	return ConstructedTextBlock;
}

TSharedRef<SButton> SAdvanceDeletionTab::ConstructButtonForRowWidget(const TSharedPtr<FAssetData>& AssetDataToDisplay)
{
	TSharedRef<SButton> ConstructedButton =
	SNew(SButton)
	.Text(FText::FromString(TEXT("Delete")))
	.OnClicked(this, &SAdvanceDeletionTab::OnDeleteButtonClicked, AssetDataToDisplay);

	return ConstructedButton;
}


FReply SAdvanceDeletionTab::OnDeleteButtonClicked(TSharedPtr<FAssetData> ClickedAssetData)
{
	FSuperManagerModule& SuperManager = FModuleManager::LoadModuleChecked<FSuperManagerModule>(TEXT("SuperManager"));
	const bool bAssetDeleted = SuperManager.DeleteSingleAssetForAssetList(*ClickedAssetData.Get());

	// Refresh the list
	if (bAssetDeleted)
	{
		if (StoredAssetDatas.Contains(ClickedAssetData))
		{
			StoredAssetDatas.Remove(ClickedAssetData);
		}

		if (DisplayAssetDatas.Contains(ClickedAssetData))
		{
			DisplayAssetDatas.Remove(ClickedAssetData);
		}
		
		RefreshAssetListView();
	}
	
	return FReply::Handled();
}

void SAdvanceDeletionTab::OnRowWidgetMouseButtonClicked(TSharedPtr<FAssetData> ClickedData)
{
	FSuperManagerModule& SuperManager = FModuleManager::LoadModuleChecked<FSuperManagerModule>(TEXT("SuperManager"));
	SuperManager.SyncContentBrowserToClickedAssetsForAssetList(ClickedData->GetObjectPathString());
}

#pragma endregion


#pragma region TabButtons

TSharedRef<SButton> SAdvanceDeletionTab::ConstructDeleteAllButton()
{
	TSharedRef<SButton> DeleteAllButton =
	SNew(SButton)
	.ContentPadding(FMargin(5.0f))
	.OnClicked(this, &SAdvanceDeletionTab::OnDeleteAllButtonClicked);

	DeleteAllButton->SetContent(ConstructTextForTabButtons(TEXT("Delete All")));
	
	return DeleteAllButton;
}

TSharedRef<SButton> SAdvanceDeletionTab::ConstructSelectAllButton()
{
	TSharedRef<SButton> SelectAllButton =
	SNew(SButton)
	.ContentPadding(FMargin(5.0f))
	.OnClicked(this, &SAdvanceDeletionTab::OnSelectAllButtonClicked);

	SelectAllButton->SetContent(ConstructTextForTabButtons(TEXT("Select All")));
	
	return SelectAllButton;
}

TSharedRef<SButton> SAdvanceDeletionTab::ConstructDeSelectAllButton()
{
	TSharedRef<SButton> DeSelectAllButton =
	SNew(SButton)
	.ContentPadding(FMargin(5.0f))
	.OnClicked(this, &SAdvanceDeletionTab::OnDeSelectAllButtonClicked);

	DeSelectAllButton->SetContent(ConstructTextForTabButtons(TEXT("DeSelect All")));
	
	return DeSelectAllButton;
}

FReply SAdvanceDeletionTab::OnDeleteAllButtonClicked()
{
	if (AssetDatasToDelete.Num() == 0)
	{
		DebugHeader::ShowMsgDialog(EAppMsgType::Ok, TEXT("No asset currently selected."));
		return FReply::Handled();
	}

	TArray<FAssetData> AssetDatasToDeleteArray;

	for (const TSharedPtr<FAssetData>& Data : AssetDatasToDelete)
	{
		AssetDatasToDeleteArray.Add(*Data.Get());
	}

	FSuperManagerModule& SuperManager = FModuleManager::LoadModuleChecked<FSuperManagerModule>(TEXT("SuperManager"));

	const bool bAssetsDeleted = SuperManager.DeleteMultipleAssetsForAssetList(AssetDatasToDeleteArray);

	if (bAssetsDeleted)
	{
		for (const TSharedPtr<FAssetData>& DeletedData : AssetDatasToDelete)
		{
			if (StoredAssetDatas.Contains(DeletedData))
			{
				StoredAssetDatas.Remove(DeletedData);
			}

			if (DisplayAssetDatas.Contains(DeletedData))
			{
				DisplayAssetDatas.Remove(DeletedData);
			}
		}
		
		RefreshAssetListView();
	}
	
	return FReply::Handled();
}

FReply SAdvanceDeletionTab::OnSelectAllButtonClicked()
{
	if (CheckBoxes.Num() == 0) return FReply::Handled();

	for (const TSharedRef<SCheckBox>& CheckBox : CheckBoxes)
	{
		if (CheckBox->IsChecked() == false)
		{
			CheckBox->ToggleCheckedState();
		}
	}
	
	return FReply::Handled();
}

FReply SAdvanceDeletionTab::OnDeSelectAllButtonClicked()
{
	if (CheckBoxes.Num() == 0) return FReply::Handled();

	for (const TSharedRef<SCheckBox>& CheckBox : CheckBoxes)
	{
		if (CheckBox->IsChecked() == true)
		{
			CheckBox->ToggleCheckedState();
		}
	}
	
	return FReply::Handled();
}

TSharedRef<STextBlock> SAdvanceDeletionTab::ConstructTextForTabButtons(const FString& TextContent)
{
	FSlateFontInfo FontInfo = GetEmbossedTextTextFont();
	FontInfo.Size = 15;
	
	TSharedRef<STextBlock> ConstructedText = 
	SNew(STextBlock)
	.Text(FText::FromString(TextContent))
	.Font(FontInfo)
	.Justification(ETextJustify::Center);

	return ConstructedText;
}

#pragma endregion


#pragma region ComboBoxForListingCondition

TSharedRef<SComboBox<TSharedPtr<FString>>> SAdvanceDeletionTab::ConstructComboBox()
{
	TSharedRef<SComboBox<TSharedPtr<FString>>> ConstructedComboBox = 
	SNew(SComboBox<TSharedPtr<FString>>)
	.OptionsSource(&ComboBoxSourceItems)
	.OnGenerateWidget(this, &SAdvanceDeletionTab::OnGenerateComboContent)
	.OnSelectionChanged(this, &SAdvanceDeletionTab::OnComboSelectionChanged)
	[
		SAssignNew(ComboDisplayTextBlock, STextBlock)
		.Text(FText::FromString(TEXT("List Assets Option")))
	];

	return ConstructedComboBox;
}

TSharedRef<SWidget> SAdvanceDeletionTab::OnGenerateComboContent(TSharedPtr<FString> SourceItem)
{
	TSharedRef<STextBlock> ConstructedComboText = 
	SNew(STextBlock)
	.Text(FText::FromString(*SourceItem.Get()));

	return ConstructedComboText;
}

void SAdvanceDeletionTab::OnComboSelectionChanged(TSharedPtr<FString> SelectedOption, ESelectInfo::Type InSelectInfo)
{
	DebugHeader::Print(*SelectedOption.Get());

	ComboDisplayTextBlock->SetText(FText::FromString(*SelectedOption.Get()));

	FSuperManagerModule& SuperManager = FModuleManager::LoadModuleChecked<FSuperManagerModule>(TEXT("SuperManager"));

	// Pass data for our module to filter
	if (SelectedOption->Equals(ListAll))
	{
		DisplayAssetDatas = StoredAssetDatas;
		RefreshAssetListView();
	}
	else if (SelectedOption->Equals(ListUnused))
	{
		SuperManager.ListUnusedAssetsForAssetList(StoredAssetDatas, DisplayAssetDatas);
		RefreshAssetListView();
	}
	else if (SelectedOption->Equals(ListSameName))
	{
		SuperManager.ListSameNameAssetsForAssetList(StoredAssetDatas, DisplayAssetDatas);
		RefreshAssetListView();
	}
}

TSharedRef<STextBlock> SAdvanceDeletionTab::ConstructComboHelpTexts(const FString& TextContent, ETextJustify::Type TextJustify)
{
	TSharedRef<STextBlock> ConstructedHelpText =
	SNew(STextBlock)
	.Text(FText::FromString(TextContent))
	.Justification(TextJustify)
	.AutoWrapText(true);

	return ConstructedHelpText;
}


#pragma endregion


TSharedRef<SListView<TSharedPtr<FAssetData>>> SAdvanceDeletionTab::ConstructAssetListView()
{
	ConstructedAssetListView = 
	SNew(SListView<TSharedPtr<FAssetData>>)
	.ItemHeight(24.0f)
	.ListItemsSource(&DisplayAssetDatas)
	.OnGenerateRow(this, &SAdvanceDeletionTab::OnGenerateRowForList)
	.OnMouseButtonClick(this, &SAdvanceDeletionTab::OnRowWidgetMouseButtonClicked);
	
	return ConstructedAssetListView.ToSharedRef();
}

void SAdvanceDeletionTab::RefreshAssetListView()
{
	// Clear the temp data array
	AssetDatasToDelete.Empty();
	CheckBoxes.Empty();
	
	if (ConstructedAssetListView.IsValid())
	{
		ConstructedAssetListView->RebuildList();
	}
}


