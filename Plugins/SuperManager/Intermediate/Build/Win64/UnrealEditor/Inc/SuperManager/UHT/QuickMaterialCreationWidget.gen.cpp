// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SuperManager/Public/AssetActions/QuickMaterialCreationWidget.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeQuickMaterialCreationWidget() {}
// Cross Module References
	BLUTILITY_API UClass* Z_Construct_UClass_UEditorUtilityWidget();
	SUPERMANAGER_API UClass* Z_Construct_UClass_UQuickMaterialCreationWidget();
	SUPERMANAGER_API UClass* Z_Construct_UClass_UQuickMaterialCreationWidget_NoRegister();
	UPackage* Z_Construct_UPackage__Script_SuperManager();
// End Cross Module References
	DEFINE_FUNCTION(UQuickMaterialCreationWidget::execCreateMaterialFromSelectedTextures)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CreateMaterialFromSelectedTextures();
		P_NATIVE_END;
	}
	void UQuickMaterialCreationWidget::StaticRegisterNativesUQuickMaterialCreationWidget()
	{
		UClass* Class = UQuickMaterialCreationWidget::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateMaterialFromSelectedTextures", &UQuickMaterialCreationWidget::execCreateMaterialFromSelectedTextures },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UQuickMaterialCreationWidget_CreateMaterialFromSelectedTextures_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UQuickMaterialCreationWidget_CreateMaterialFromSelectedTextures_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AssetActions/QuickMaterialCreationWidget.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UQuickMaterialCreationWidget_CreateMaterialFromSelectedTextures_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UQuickMaterialCreationWidget, nullptr, "CreateMaterialFromSelectedTextures", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UQuickMaterialCreationWidget_CreateMaterialFromSelectedTextures_Statics::Function_MetaDataParams), Z_Construct_UFunction_UQuickMaterialCreationWidget_CreateMaterialFromSelectedTextures_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UQuickMaterialCreationWidget_CreateMaterialFromSelectedTextures()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UQuickMaterialCreationWidget_CreateMaterialFromSelectedTextures_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UQuickMaterialCreationWidget);
	UClass* Z_Construct_UClass_UQuickMaterialCreationWidget_NoRegister()
	{
		return UQuickMaterialCreationWidget::StaticClass();
	}
	struct Z_Construct_UClass_UQuickMaterialCreationWidget_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bCustomMaterialName_MetaData[];
#endif
		static void NewProp_bCustomMaterialName_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bCustomMaterialName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaterialName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_MaterialName;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UEditorUtilityWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_SuperManager,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UQuickMaterialCreationWidget_CreateMaterialFromSelectedTextures, "CreateMaterialFromSelectedTextures" }, // 2876614322
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "AssetActions/QuickMaterialCreationWidget.h" },
		{ "ModuleRelativePath", "Public/AssetActions/QuickMaterialCreationWidget.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_bCustomMaterialName_MetaData[] = {
		{ "Category", "CreateMaterialFromSelectedTextures" },
		{ "ModuleRelativePath", "Public/AssetActions/QuickMaterialCreationWidget.h" },
	};
#endif
	void Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_bCustomMaterialName_SetBit(void* Obj)
	{
		((UQuickMaterialCreationWidget*)Obj)->bCustomMaterialName = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_bCustomMaterialName = { "bCustomMaterialName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UQuickMaterialCreationWidget), &Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_bCustomMaterialName_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_bCustomMaterialName_MetaData), Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_bCustomMaterialName_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_MaterialName_MetaData[] = {
		{ "Category", "CreateMaterialFromSelectedTextures" },
		{ "EditCondition", "bCustomMaterialName" },
		{ "ModuleRelativePath", "Public/AssetActions/QuickMaterialCreationWidget.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_MaterialName = { "MaterialName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UQuickMaterialCreationWidget, MaterialName), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_MaterialName_MetaData), Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_MaterialName_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_bCustomMaterialName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::NewProp_MaterialName,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQuickMaterialCreationWidget>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::ClassParams = {
		&UQuickMaterialCreationWidget::StaticClass,
		"Editor",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::PropPointers),
		0,
		0x00B010A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::Class_MetaDataParams), Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UQuickMaterialCreationWidget()
	{
		if (!Z_Registration_Info_UClass_UQuickMaterialCreationWidget.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UQuickMaterialCreationWidget.OuterSingleton, Z_Construct_UClass_UQuickMaterialCreationWidget_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UQuickMaterialCreationWidget.OuterSingleton;
	}
	template<> SUPERMANAGER_API UClass* StaticClass<UQuickMaterialCreationWidget>()
	{
		return UQuickMaterialCreationWidget::StaticClass();
	}
	UQuickMaterialCreationWidget::UQuickMaterialCreationWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UQuickMaterialCreationWidget);
	UQuickMaterialCreationWidget::~UQuickMaterialCreationWidget() {}
	struct Z_CompiledInDeferFile_FID_Unreal_Projects_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_AssetActions_QuickMaterialCreationWidget_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_AssetActions_QuickMaterialCreationWidget_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UQuickMaterialCreationWidget, UQuickMaterialCreationWidget::StaticClass, TEXT("UQuickMaterialCreationWidget"), &Z_Registration_Info_UClass_UQuickMaterialCreationWidget, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UQuickMaterialCreationWidget), 3261224722U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_AssetActions_QuickMaterialCreationWidget_h_2033781516(TEXT("/Script/SuperManager"),
		Z_CompiledInDeferFile_FID_Unreal_Projects_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_AssetActions_QuickMaterialCreationWidget_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_ExtendEditor_Plugins_SuperManager_Source_SuperManager_Public_AssetActions_QuickMaterialCreationWidget_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
