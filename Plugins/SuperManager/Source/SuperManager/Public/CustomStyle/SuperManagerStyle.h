// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

struct FSuperManagerStyle
{
private:
	static FName StyleSetName;
	static TSharedPtr<FSlateStyleSet> CreatedSlateStyleSet;

public:
	static void InitializedIcons();
	static void ShutDown();

public:
	static FName GetStyleSetName() { return StyleSetName; };

private:
	static TSharedRef<FSlateStyleSet> CreateSlateStyleSet();
};

