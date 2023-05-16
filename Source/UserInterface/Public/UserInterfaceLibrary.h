#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInterfaceLibrary.generated.h"

USTRUCT(BlueprintType)
struct FWidgetRect
{
	GENERATED_BODY()

	/*
	--------Top--------
	|                 |
	Left     0    Right
	|                 |
	-------Bottom------
	*/

	float Left, Right, Top, Bottom;

	FWidgetRect() : Left(0), Right(0), Top(0), Bottom(0) {}
	FWidgetRect(float InLeft, float InRight, float InTop, float InBottom) : Left(InLeft), Right(InRight), Top(InTop), Bottom(InBottom) {}

	bool Contains(const FVector2D& InPoint) const;	
	bool Overlap(const FWidgetRect& InOther) const;
	float Area() const;
	float OverlapArea(const FWidgetRect& InOther) const;
};

UCLASS(Abstract)
class USERINTERFACE_API UUserInterfaceLibrary : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FVector2D GetAbsolutePosition(UWidget* InWidget);

	/*
	* InBaseWidget: 해당 위젯에서의 로컬위치인 InWidgetLocalPosition를 기준으로 삼게 됩니다.
	* InWidgetLocalPosition: 절대 좌표로 변환할 좌표입니다.
	*/
	UFUNCTION(BlueprintCallable)
	static FVector2D LocalToAbsolute(UWidget* InBaseWidget, const FVector2D& InWidgetLocalPosition);

	UFUNCTION(BlueprintCallable)
	static FVector2D AbsoluteToLocal(UWidget* InBaseWidget, const FVector2D& InAbsolutePosition);

	UFUNCTION(BlueprintCallable)
	static FVector2D GetLocalPositionOf(UWidget* InBaseWidget, UWidget* InWidget);

	UFUNCTION(BlueprintCallable)
	static FVector2D GetMousePositionOnAbsolute(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static FVector2D GetMousePositionOnLocal(UWidget* InBaseWidget);

	UFUNCTION(BlueprintCallable)
	static FWidgetRect GetWidgetRectOnAbsolute(UWidget* InWidget);

	UFUNCTION(BlueprintCallable)
	static bool WidgetOverlapOnAbsolute(UWidget* InWidgetA, UWidget* InWidgetB);

	UFUNCTION(BlueprintCallable)
	static float WidgetOverlapAreaOnAbsolute(UWidget* InWidgetA, UWidget* InWidgetB);

	UFUNCTION(BlueprintCallable)
	static FVector2D GetWidgetSizeOnAbsolute(UWidget* InWidget);
};

