// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "QuickMaterialCreationWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANAGER_API UQuickMaterialCreationWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
#pragma region QuickMaterialCreationCore

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateMaterialFromSelectedTextures")
	bool bCustomMaterialName = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateMaterialFromSelectedTextures", meta = (EditCondition = "bCustomMaterialName"))
	FString MaterialName = TEXT("M_");
	
	UFUNCTION(BlueprintCallable)
	void CreateMaterialFromSelectedTextures();

#pragma endregion

private:
#pragma region QuickMaterialCreation

	bool ProcessSelectionData(const TArray<FAssetData>& SelectedDataToProcess, TArray<UTexture2D*>& OutSelectedTextures, FString& OutSelectedPackagePath);

	bool ChekcIsNameUsed(const FString& FolderPathToCheck, const FString& MaterialNameToCheck);
	
#pragma endregion

};
