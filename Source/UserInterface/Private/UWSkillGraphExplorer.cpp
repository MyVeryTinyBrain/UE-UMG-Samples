// Fill out your copyright notice in the Description page of Project Settings.


#include "UWSkillGraphExplorer.h"
#include <Components/CanvasPanel.h>
#include "UWSkillGraph.h"
#include <Components/CanvasPanelSlot.h>
#include <Blueprint/GameViewportSubsystem.h>
#include "UWSkillNode.h"
#include <Engine/Engine.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Components/Image.h>
#include "UWSizableTextBlock.h"
#include <SkillMapData.h>
#include "UserInterfaceLibrary.h"

void UUWSkillGraphExplorer::NativeOnHeroGalleryWidgetSetup()
{
	Super::NativeOnHeroGalleryWidgetSetup();
	
	UpdateSkillGraph();
	if (SkillGraph && SubData.SkillMapDataTable)
	{
		UDataTable* SkillDataTable = FSkillMapData::FindSkillDataTable(SubData.SkillMapDataTable, SubData.HeroType);
		SkillGraph->Setup(UserData, SkillDataTable, SubData.HeroType);
	}
}

void UUWSkillGraphExplorer::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_DragArea->OnPressed.AddDynamic(this, &UUWSkillGraphExplorer::OnDragAreaPressed);
	Btn_DragArea->OnReleased.AddDynamic(this, &UUWSkillGraphExplorer::OnDragAreaReleased);

	PrevMousePositionInViewport = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	WBSTB_TextBlock->SetVisibility(ESlateVisibility::Collapsed);
}

void UUWSkillGraphExplorer::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateSkillGraph();
}

void UUWSkillGraphExplorer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Zoom
	float AbsMouseWheelDelta = FMath::Abs(MouseWheelDelta);
	float SignMouseeWheelDelta = FMath::Sign(MouseWheelDelta);
	AbsMouseWheelDelta = FMath::Lerp(AbsMouseWheelDelta, 0.0f, InDeltaTime * ZoomDeltaDecreasePower);
	if (AbsMouseWheelDelta < 0.1f)
		AbsMouseWheelDelta = 0;
	MouseWheelDelta = AbsMouseWheelDelta * SignMouseeWheelDelta;
	FWidgetTransform SkillGraphTransform = SkillGraph->GetRenderTransform();
	if (SkillGraph)
	{
		SkillGraphTransform.Scale.X = FMath::Clamp(SkillGraphTransform.Scale.X + MouseWheelDelta * InDeltaTime, MinZoomScale, MaxZoomScale);
		SkillGraphTransform.Scale.Y = FMath::Clamp(SkillGraphTransform.Scale.Y + MouseWheelDelta * InDeltaTime, MinZoomScale, MaxZoomScale);
		SkillGraph->SetRenderTransform(SkillGraphTransform);
	}

	// Drag
	FVector2D MousePositionInViewport = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	if (bIsDrag)
	{
		MouseDelta = MousePositionInViewport - PrevMousePositionInViewport;
	}
	else
	{
		MouseDelta = FMath::Lerp(MouseDelta, FVector2D::ZeroVector, InDeltaTime * DragDeltaDecreasePower);
		FVector2D AbsMouseDelta = MouseDelta.GetAbs();
		if (AbsMouseDelta.X < 10)
			MouseDelta.X = 0;
		if (AbsMouseDelta.Y < 10)
			MouseDelta.Y = 0;
	}
	PrevMousePositionInViewport = MousePositionInViewport;
	if (SkillGraph)
	{
		UCanvasPanelSlot* skillGraphCanvasPanelSlot = Cast<UCanvasPanelSlot>(SkillGraph->Slot);
		FVector2D NewSkillGraphPos = skillGraphCanvasPanelSlot->GetPosition() + MouseDelta;
		ClampPosition(NewSkillGraphPos, skillGraphCanvasPanelSlot->GetSize(), SkillGraphTransform.Scale);
		skillGraphCanvasPanelSlot->SetPosition(NewSkillGraphPos);
	}
}

FReply UUWSkillGraphExplorer::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	MouseWheelDelta = InMouseEvent.GetWheelDelta();
	return Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
}

void UUWSkillGraphExplorer::OnDragAreaPressed()
{
	bIsDrag = true;
}

void UUWSkillGraphExplorer::OnDragAreaReleased()
{
	bIsDrag = false;
}

void UUWSkillGraphExplorer::OnSkillNodeHovered(UUWSkillNode* SkillNode, bool IsInteractible)
{
	WBSTB_TextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	const FSkillData& Data = SkillNode->GetSkillData();
	FString Description = Data.SkillName + TEXT("\n") + Data.SkillDescription;
	WBSTB_TextBlock->SetText(FText::FromString(Description));
}

void UUWSkillGraphExplorer::OnSkillNodeUnhovered(UUWSkillNode* SkillNode, bool IsInteractible)
{
	WBSTB_TextBlock->SetVisibility(ESlateVisibility::Collapsed);
}

UUWSkillGraph* UUWSkillGraphExplorer::SetSkillGraph(EHeroType Type)
{
	MouseDelta = FVector2D::ZeroVector;
	MouseWheelDelta = 0;

	TSubclassOf<class UUWSkillGraph>* SkillGraphTemplate = SkillGraphsByHero.Find(Type);
	if (!SkillGraphTemplate || !IsValid(*SkillGraphTemplate))
		return nullptr;
	
	UUWSkillGraph* element = CreateWidget<UUWSkillGraph>(Canv_Root, *SkillGraphTemplate);
	if (SkillGraph)
		Canv_Root->RemoveChild(SkillGraph);
	Canv_Root->AddChild(element);
	
	UCanvasPanelSlot* elementCanvasPanelSlot = Cast<UCanvasPanelSlot>(element->Slot);
	if (!elementCanvasPanelSlot)
		return nullptr;

	elementCanvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
	elementCanvasPanelSlot->SetOffsets(FMargin(0, 0, 0, 0));
	elementCanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));

	// Fit Panel And Nodes
	FVector2D NodeAreaSize = element->GetNodeAreaSize();
	elementCanvasPanelSlot->SetSize(NodeAreaSize);

	for (UUWSkillNode* Node : element->GetNodes())
	{
		UCanvasPanelSlot* nodeCanvasPanelSlot = Cast<UCanvasPanelSlot>(Node->Slot);
		nodeCanvasPanelSlot->SetPosition(nodeCanvasPanelSlot->GetPosition() - element->GetCenterOfNodeArea());
	}

	// Focus Root Node
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport)
	{
		if (UUWSkillNode* RootSkillNode = element->GetRootSkillNode())
		{
			FVector2D LocalNodePos = UUserInterfaceLibrary::GetLocalPositionOf(Canv_Root, RootSkillNode);
			FVector2D TranslateVec = -LocalNodePos;
			elementCanvasPanelSlot->SetPosition(elementCanvasPanelSlot->GetPosition() + TranslateVec);
		}
	}

	element->OnSkillNodeHovered.AddDynamic(this, &UUWSkillGraphExplorer::OnSkillNodeHovered);
	element->OnSkillNodeUnhovered.AddDynamic(this, &UUWSkillGraphExplorer::OnSkillNodeUnhovered);

	return element;
}

void UUWSkillGraphExplorer::ClampPosition(FVector2D& Position, FVector2D Size, FVector2D Scale)
{
	Size *= Scale;
	FVector2D HalfGraphSize = Size * 0.5f;

	float Left = FMath::Abs(Position.X - HalfGraphSize.X);
	float Right = Position.X + HalfGraphSize.X;
	float Top = FMath::Abs(Position.Y - HalfGraphSize.Y);
	float Bottom = Position.Y + HalfGraphSize.Y;
	FVector2D RootCanvasSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	USlateBlueprintLibrary::ScreenToWidgetLocal(GetWorld(), Canv_Root->GetCachedGeometry(), RootCanvasSize, RootCanvasSize);
	FVector2D HalfRootCanvasSize = RootCanvasSize * 0.5f;

	if (Size.X > RootCanvasSize.X)
	{
		if (Left < HalfRootCanvasSize.X)
			Position.X -= HalfRootCanvasSize.X - Left;
		else if (Right < HalfRootCanvasSize.X)
			Position.X += HalfRootCanvasSize.X - Right;
	}
	else
	{
		Position.X = 0;
	}

	if (Size.Y > RootCanvasSize.Y)
	{
		if (Top < HalfRootCanvasSize.Y)
			Position.Y -= HalfRootCanvasSize.Y - Top;
		else if (Bottom < HalfRootCanvasSize.Y)
			Position.Y += HalfRootCanvasSize.Y - Bottom;
	}
	else
	{
		Position.Y = 0;
	}
}

void UUWSkillGraphExplorer::UpdateSkillGraph()
{
	SkillGraph = SetSkillGraph(SubData.HeroType);
}

void UUWSkillGraphExplorer::SetMinZoomScale(float InMinZoomScale)
{
	MinZoomScale = InMinZoomScale;
}

void UUWSkillGraphExplorer::SetMaxZoomScale(float InMaxZoomScale)
{
	MaxZoomScale = InMaxZoomScale;
}
