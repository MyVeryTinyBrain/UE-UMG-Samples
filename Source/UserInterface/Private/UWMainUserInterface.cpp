// Fill out your copyright notice in the Description page of Project Settings.


#include "UWMainUserInterface.h"
#include "UWTextButton.h"
#include <Components/CanvasPanelSlot.h>
#include "UserDataWidget.h"
#include <UserData.h>
#include "UWMainGlobalWidgets.h"
#include <Components/CanvasPanel.h>
#include "UWMainGlobalWidgets.h"
#include "UWFade.h"
#include "UWButton.h"

#define UserDataWidgetZOrder 10000
#define MainGlobalWidgetsZOrder 100000

void UUWMainUserInterface::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup Main Global Widgets
	MainGlobalWidgets = CreateWidget<UUWMainGlobalWidgets>(Canv_Root, MainGlobalWidgetsTemplate);
	Canv_Root->AddChild(MainGlobalWidgets);

	if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(MainGlobalWidgets->Slot))
	{
		CanvasPanelSlot->SetAnchors(FAnchors(0, 0, 1, 1));
		CanvasPanelSlot->SetOffsets(FMargin(0, 0, 0, 0));
		CanvasPanelSlot->SetZOrder(MainGlobalWidgetsZOrder);
	}

	MainGlobalWidgets->GetEscapeButton()->OnClicked.AddDynamic(this, &UUWMainUserInterface::OnEscapeButtonClicked);
	MainGlobalWidgets->GetFade()->OnFadeInEnded.AddDynamic(this, &UUWMainUserInterface::OnFadeInEnded);

	// Hide Escape Button
	MainGlobalWidgets->GetEscapeButton()->SetVisibility(ESlateVisibility::Collapsed);

	// Initialize Current Widget
	CurrentWidget = Canv_Main;

	// Bind Buttons
	WBTB_Loot->OnTextButtonClicked.AddDynamic(this, &UUWMainUserInterface::OnTextButtonClicked);
	WBTB_SkillTree->OnTextButtonClicked.AddDynamic(this, &UUWMainUserInterface::OnTextButtonClicked);
	WBTB_Item->OnTextButtonClicked.AddDynamic(this, &UUWMainUserInterface::OnTextButtonClicked);
	WBTB_Exit->OnTextButtonClicked.AddDynamic(this, &UUWMainUserInterface::OnTextButtonClicked);
}

void UUWMainUserInterface::OnTextButtonClicked(UUWTextButton* InTextButton)
{
	if (InTextButton == WBTB_Loot)
	{
		SetupUserDataWidget(LootWidgetTemplate);
	}
	else if (InTextButton == WBTB_SkillTree)
	{
		SetupUserDataWidget(SkillTreeWidgetTemplate);
	}
	else if (InTextButton == WBTB_Item)
	{
		SetupUserDataWidget(ItemWidgetTemplate);
	}
	else if (InTextButton == WBTB_Exit)
	{
		#if UE_BUILD_SHIPPING
		FGenericPlatformMisc::RequestExit(false);
		#endif
	}
}

void UUWMainUserInterface::OnEscapeButtonClicked()
{
	UUWFade* Fade = MainGlobalWidgets ? MainGlobalWidgets->GetFade() : nullptr;

	if (!Fade || Fade->IsWorking())
	{
		return;
	}

	// Check And Pop from prev widget stack
	if (!MainGlobalWidgets->TryPopFromPrevWidgetStack(this))
	{
		return;
	}

	// Fade In
	Fade->Fade(0.5f, 0.1f, 0.5f);

	// Set Next Widget
	NextWidget = Canv_Main;
}

void UUWMainUserInterface::OnFadeInEnded()
{
	if (CurrentWidget && NextWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
		NextWidget->SetVisibility(ESlateVisibility::Visible);

		CurrentWidget = NextWidget;
		NextWidget = nullptr;

		if (CurrentWidget == Canv_Main)
		{
			// Hide Escape Button
			MainGlobalWidgets->GetEscapeButton()->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			// Show Escape Button
			MainGlobalWidgets->GetEscapeButton()->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

UUserDataWidget* UUWMainUserInterface::SetupUserDataWidget(TSubclassOf<class UUserDataWidget> InUserDataWidget)
{
	UUWFade* Fade = MainGlobalWidgets ? MainGlobalWidgets->GetFade() : nullptr;

	if (!Fade || Fade->IsWorking())
	{
		return nullptr;
	}

	// Create New User Data Widget
	UUserDataWidget* NewUUserDataWidget = CreateWidget<UUserDataWidget>(Canv_Root, InUserDataWidget);
	if (!NewUUserDataWidget)
	{
		return nullptr;
	}

	if (CurrentUserDataWidget)
	{
		Canv_Root->RemoveChild(CurrentUserDataWidget);
		CurrentUserDataWidget = nullptr;
	}
	Canv_Root->AddChild(NewUUserDataWidget);
	CurrentUserDataWidget = NewUUserDataWidget;

	if (UCanvasPanelSlot* WidgetCanvasPanelSlot = Cast<UCanvasPanelSlot>(CurrentUserDataWidget->Slot))
	{
		WidgetCanvasPanelSlot->SetZOrder(UserDataWidgetZOrder);
		WidgetCanvasPanelSlot->SetAnchors(FAnchors(0, 0, 1, 1));
		WidgetCanvasPanelSlot->SetOffsets(FMargin(0, 0, 0, 0));
	}
	CurrentUserDataWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Initialize New User Data Widget
	CurrentUserDataWidget->Setup(UserData);

	// Fade In
	Fade->Fade(0.5f, 0.1f, 0.5f);

	// Set Next Widget
	NextWidget = CurrentUserDataWidget;

	// Push Prev Widget
	MainGlobalWidgets->PushToPrevWidgetStack(this);

	return CurrentUserDataWidget;
}

void UUWMainUserInterface::InitalizeMainUserInterface(UUserData* InUserData)
{
	UserData = InUserData;
}
