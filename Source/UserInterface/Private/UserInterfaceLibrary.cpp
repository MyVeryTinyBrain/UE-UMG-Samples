#include "UserInterfaceLibrary.h"
#include <Components/PanelWidget.h>
#include <Components/CanvasPanelSlot.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Blueprint/SlateBlueprintLibrary.h>

FVector2D UUserInterfaceLibrary::GetAbsolutePosition(UWidget* InWidget)
{
	UPanelWidget* ParentWidget = InWidget->GetParent();
	UCanvasPanelSlot* WidgetCanvasPanelSlot = Cast<UCanvasPanelSlot>(InWidget->Slot);
	if (ParentWidget && WidgetCanvasPanelSlot)
	{
		return ParentWidget->GetCachedGeometry().LocalToAbsolute(WidgetCanvasPanelSlot->GetPosition());
	}
	return InWidget->GetCachedGeometry().GetAbsolutePosition();
}

FVector2D UUserInterfaceLibrary::LocalToAbsolute(UWidget* InBaseWidget, const FVector2D& InWidgetLocalPosition)
{
	return InBaseWidget->GetCachedGeometry().LocalToAbsolute(InWidgetLocalPosition);
}

FVector2D UUserInterfaceLibrary::AbsoluteToLocal(UWidget* InBaseWidget, const FVector2D& InAbsolutePosition)
{
	return InBaseWidget->GetCachedGeometry().AbsoluteToLocal(InAbsolutePosition);
}

FVector2D UUserInterfaceLibrary::GetLocalPositionOf(UWidget* InBaseWidget, UWidget* InWidget)
{
	FVector2D InAbsolute = GetAbsolutePosition(InWidget);
	return InBaseWidget->GetCachedGeometry().AbsoluteToLocal(InAbsolute);
}

FVector2D UUserInterfaceLibrary::GetMousePositionOnAbsolute(UObject* WorldContextObject)
{
	FVector2D MouseInViewport = UWidgetLayoutLibrary::GetMousePositionOnViewport(WorldContextObject);
	return UWidgetLayoutLibrary::GetViewportWidgetGeometry(WorldContextObject).LocalToAbsolute(MouseInViewport);
}

FVector2D UUserInterfaceLibrary::GetMousePositionOnLocal(UWidget* InBaseWidget)
{
	FVector2D MouseInAbsolute = GetMousePositionOnAbsolute(InBaseWidget->GetWorld());
	return InBaseWidget->GetCachedGeometry().AbsoluteToLocal(MouseInAbsolute);
}

FWidgetRect UUserInterfaceLibrary::GetWidgetRectOnAbsolute(UWidget* InWidget)
{
	if (UCanvasPanelSlot* WidgetCanvasPanelSlot = Cast<UCanvasPanelSlot>(InWidget->Slot))
	{
		FVector2D WidgetLTInLocal = WidgetCanvasPanelSlot->GetPosition();
		FVector2D WidgetRBInLocal = WidgetLTInLocal + WidgetCanvasPanelSlot->GetSize();
		FVector2D WidgetLTInAbsolute = LocalToAbsolute(InWidget->GetParent(), WidgetLTInLocal);
		FVector2D WidgetRBInAbsolute = LocalToAbsolute(InWidget->GetParent(), WidgetRBInLocal);
		return FWidgetRect(WidgetLTInAbsolute.X, WidgetRBInAbsolute.X, WidgetLTInAbsolute.Y, WidgetRBInAbsolute.Y);
	}
	return FWidgetRect();
}

bool UUserInterfaceLibrary::WidgetOverlapOnAbsolute(UWidget* InWidgetA, UWidget* InWidgetB)
{
	FWidgetRect A = GetWidgetRectOnAbsolute(InWidgetA);
	FWidgetRect B = GetWidgetRectOnAbsolute(InWidgetB);
	return A.Overlap(B);
}

float UUserInterfaceLibrary::WidgetOverlapAreaOnAbsolute(UWidget* InWidgetA, UWidget* InWidgetB)
{
	FWidgetRect A = GetWidgetRectOnAbsolute(InWidgetA);
	FWidgetRect B = GetWidgetRectOnAbsolute(InWidgetB);
	return A.OverlapArea(B);
}

FVector2D UUserInterfaceLibrary::GetWidgetSizeOnAbsolute(UWidget* InWidget)
{
	if (UCanvasPanelSlot* WidgetCanvasPanelSlot = Cast<UCanvasPanelSlot>(InWidget->Slot))
	{
		FVector2D WidgetLTInLocal = WidgetCanvasPanelSlot->GetPosition();
		FVector2D WidgetRBInLocal = WidgetLTInLocal + WidgetCanvasPanelSlot->GetSize();
		FVector2D WidgetLTInAbsolute = LocalToAbsolute(InWidget->GetParent(), WidgetLTInLocal);
		FVector2D WidgetRBInAbsolute = LocalToAbsolute(InWidget->GetParent(), WidgetRBInLocal);
		return FVector2D(
			FMath::Abs(WidgetRBInAbsolute.X - WidgetLTInAbsolute.X),
			FMath::Abs(WidgetRBInAbsolute.Y - WidgetLTInAbsolute.Y)
		);
	}
	return FVector2D::ZeroVector;
}

bool FWidgetRect::Contains(const FVector2D& InPoint) const
{
	if (InPoint.X >= Left && 
		InPoint.X <= Right && 
		InPoint.Y >= Top && 
		InPoint.Y <= Bottom)
	{
		return true;
	}
	return false;
}

bool FWidgetRect::Overlap(const FWidgetRect& InOther) const
{
	if (Left <= InOther.Right &&
		Right >= InOther.Left &&
		Top <= InOther.Bottom &&
		Bottom >= InOther.Top)
	{
		return true;
	}
	return false;
}

float FWidgetRect::Area() const
{
	return (Right - Left) * (Bottom - Top);
}

float FWidgetRect::OverlapArea(const FWidgetRect& InOther) const
{
	if (Overlap(InOther))
	{
		float IntersectionLeft = FMath::Max(Left, InOther.Left);
		float IntersectionRight = FMath::Min(Right, InOther.Right);
		float IntersectionTop = FMath::Max(Top, InOther.Top);
		float IntersectionBottom = FMath::Min(Bottom, InOther.Bottom);
		return (IntersectionRight - IntersectionLeft) * (IntersectionBottom - IntersectionTop);
	}
	return 0.0f;
}
