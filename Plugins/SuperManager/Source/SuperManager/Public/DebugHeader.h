#pragma once
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

inline void Print(const FString& Message, const FColor& Color = FColor::Green)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.0f, Color, Message);
	}
}

inline void PrintLog(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}

inline EAppReturnType::Type ShowMsgDialog(EAppMsgType::Type MsgType, const FString& Message, bool bShowMsgAsWarning = true)
{
	if (bShowMsgAsWarning)
	{
		const FText MsgTitle = FText::FromString(TEXT("Warning"));
		return FMessageDialog::Open(MsgType, FText::FromString(Message), MsgTitle);
	}
	else
	{
		return FMessageDialog::Open(MsgType, FText::FromString(Message));
	}
}

inline void ShowNotifyInfo(const FString& Message)
{
	FNotificationInfo NotifiInfo(FText::FromString(Message));
	NotifiInfo.bUseLargeFont = true;
	NotifiInfo.FadeOutDuration = 7.0f;

	FSlateNotificationManager::Get().AddNotification(NotifiInfo);
}