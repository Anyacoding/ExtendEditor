// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWidgets/AdvanceDeletionWidget.h"
#include "DebugHeader.h"
#include "SuperManager.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAdvanceDeletionTab::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	FSlateFontInfo TitleTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
	TitleTextFont.Size = 30;

	StoredAssetDatas = InArgs._AssetDatasToStore;
	
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
		[
			SNew(SHorizontalBox)
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
		.FillWidth(0.05f)
		[
			ConstructCheckBox(AssetDataToDisplay)
		]
		// Second slot for displaying asset class name
		+SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.FillWidth(0.3f)
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

	return ConstructedCheckBox;
}

void SAdvanceDeletionTab::OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> AssetData)
{
	switch (NewState)
	{
	case ECheckBoxState::Checked:
		DebugHeader::Print(TEXT("Checked"), FColor::Green);
		break;
	case ECheckBoxState::Unchecked:
		DebugHeader::Print(TEXT("Unchecked"), FColor::Red);
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
		RefreshAssetListView();
	}
	
	return FReply::Handled();
}

#pragma endregion

TSharedRef<SListView<TSharedPtr<FAssetData>>> SAdvanceDeletionTab::ConstructAssetListView()
{
	ConstructedAssetListView = 
	SNew(SListView<TSharedPtr<FAssetData>>)
	.ItemHeight(24.0f)
	.ListItemsSource(&StoredAssetDatas)
	.OnGenerateRow(this, &SAdvanceDeletionTab::OnGenerateRowForList);
	
	return ConstructedAssetListView.ToSharedRef();
}

void SAdvanceDeletionTab::RefreshAssetListView() const
{
	if (ConstructedAssetListView.IsValid())
	{
		ConstructedAssetListView->RebuildList();
	}
}


