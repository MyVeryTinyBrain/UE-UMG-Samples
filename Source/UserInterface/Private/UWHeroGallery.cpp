// Fill out your copyright notice in the Description page of Project Settings.


#include "UWHeroGallery.h"
#include "UWHeroList.h"
#include "UWItemGallery.h"
#include "UWFade.h"
#include <Components/CanvasPanel.h>
#include "UWButton.h"
#include "HeroGalleryWidget.h"
#include <Components/CanvasPanelSlot.h>
#include "UWMainGlobalWidgets.h"

#define HeroGalleryWidgetZOrder 10000

void UUWHeroGallery::NativePreConstruct()
{
	Super::NativePreConstruct();

	Update();
}

void UUWHeroGallery::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentWidget = Canv_HeroGallery;

	WBHL_HeroList->OnHeroButtonClickedA.AddDynamic(this, &UUWHeroGallery::OnHeroButtonClicked);

	if (UUWMainGlobalWidgets* MainGlobalWidgets = UUWMainGlobalWidgets::GetMainGlobalWidgets())
	{
		MainGlobalWidgets->GetEscapeButton()->OnClicked.AddDynamic(this, &UUWHeroGallery::OnEscapeButtonClicked);
		MainGlobalWidgets->GetFade()->OnFadeInEnded.AddDynamic(this, &UUWHeroGallery::OnFadeInEnded);
	}
}

void UUWHeroGallery::OnHeroButtonClicked(const FHeroDesc& HeroDesc)
{
	UUWMainGlobalWidgets* MainGlobalWidgets = UUWMainGlobalWidgets::GetMainGlobalWidgets();
	UUWFade* Fade = MainGlobalWidgets ? MainGlobalWidgets->GetFade() : nullptr;

	if (!Fade || Fade->IsWorking())
	{
		return;
	}

	if (!UserData || !HeroGalleryWidgetTemplate)
	{
		return;
	}

	// Create New Hero Gallery Widget
	UHeroGalleryWidget* NewHeroGalleryWidget = CreateWidget<UHeroGalleryWidget>(Canv_Root, HeroGalleryWidgetTemplate);
	if (!NewHeroGalleryWidget)
	{
		return;
	}

	if (CurrentHeroGalleryWidget)
	{
		Canv_Root->RemoveChild(CurrentHeroGalleryWidget);
		CurrentHeroGalleryWidget = nullptr;
	}
	Canv_Root->AddChild(NewHeroGalleryWidget);
	CurrentHeroGalleryWidget = NewHeroGalleryWidget;

	if (UCanvasPanelSlot* WidgetCanvasPanelSlot = Cast<UCanvasPanelSlot>(CurrentHeroGalleryWidget->Slot))
	{
		WidgetCanvasPanelSlot->SetZOrder(HeroGalleryWidgetZOrder);
		WidgetCanvasPanelSlot->SetAnchors(FAnchors(0, 0, 1, 1));
		WidgetCanvasPanelSlot->SetOffsets(FMargin(0, 0, 0, 0));
	}
	CurrentHeroGalleryWidget->SetVisibility(ESlateVisibility::Collapsed);

	// Initialize New Hero Gallery Widget
	FHeroGalleryWidgetSubData SubData;
	SubData.HeroType = HeroDesc.HeroType;
	SubData.HeroName = HeroDesc.HeroName;
	SubData.HeroDescriptionsTable = HeroDescriptionsTable;
	SubData.ItemMapDataTable = ItemMapDataTable;
	SubData.SkillMapDataTable = SkillMapDataTable;
	CurrentHeroGalleryWidget->Setup(UserData, SubData);

	// Fade In
	Fade->Fade(0.5f, 0.1f, 0.5f);

	// Fade In
	NextWidget = CurrentHeroGalleryWidget;

	// Push Prev Widget
	MainGlobalWidgets->PushToPrevWidgetStack(this);
}

void UUWHeroGallery::OnEscapeButtonClicked()
{
	UUWMainGlobalWidgets* MainGlobalWidgets = UUWMainGlobalWidgets::GetMainGlobalWidgets();
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
	NextWidget = Canv_HeroGallery;
}

void UUWHeroGallery::OnFadeInEnded()
{
	if (CurrentWidget && NextWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
		NextWidget->SetVisibility(ESlateVisibility::Visible);

		CurrentWidget = NextWidget;
		NextWidget = nullptr;
	}
}

void UUWHeroGallery::Update()
{
	if (HeroDescriptionsTable != nullptr)
	{
		const TArray<FHeroDesc>& HeroDescriptions = FHeroDesc::ExtractTable(HeroDescriptionsTable);
		WBHL_HeroList->SetHeroDescriptions(HeroDescriptions);
	}
}
