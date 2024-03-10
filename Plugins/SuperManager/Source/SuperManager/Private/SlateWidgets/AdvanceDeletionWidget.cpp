// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWidgets/AdvanceDeletionWidget.h"
#include "DebugHeader.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAdvanceDeletionTab::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;

	FSlateFontInfo TitleTextFont = FCoreStyle::Get().GetFontStyle(FName("EmbossedText"));
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
			.Text(FText::FromString(InArgs._TestString))
			.Font(TitleTextFont)
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FColor::White)
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION