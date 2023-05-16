// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <HeroData.h>
#include "HeroGalleryWidget.h"
#include "Blueprint/UserWidget.h"
#include "UWSkillGraphExplorer.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWSkillGraphExplorer : public UHeroGalleryWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TMap<EHeroType, TSubclassOf<class UUWSkillGraph>> SkillGraphsByHero;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canv_Root;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_DragArea;

	UPROPERTY(meta = (BindWidget))
	class UUWSizableTextBlock* WBSTB_TextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UUWSkillGraph> SkillGraph;

	FVector2D PrevMousePositionInViewport;
	FVector2D MouseDelta = FVector2D::ZeroVector;
	bool bIsDrag = false;
	float MouseWheelDelta = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float DragDeltaDecreasePower = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float MinZoomScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float MaxZoomScale = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float ZoomDeltaDecreasePower = 5.0f;

protected:
	virtual void NativeOnHeroGalleryWidgetSetup();
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	virtual void OnDragAreaPressed();

	UFUNCTION()
	virtual void OnDragAreaReleased();

	UFUNCTION()
	virtual void OnSkillNodeHovered(class UUWSkillNode* SkillNode, bool IsInteractible);

	UFUNCTION()
	virtual void OnSkillNodeUnhovered(class UUWSkillNode* SkillNode, bool IsInteractible);

private:
	class UUWSkillGraph* SetSkillGraph(EHeroType Type);
	void ClampPosition(FVector2D& Position, FVector2D Size, FVector2D Scale);

	void UpdateSkillGraph();

public:
	UFUNCTION(BlueprintCallable)
	float GetMinZoomScale() const { return MinZoomScale; }

	UFUNCTION(BlueprintCallable)
	void SetMinZoomScale(float InMinZoomScale);

	UFUNCTION(BlueprintCallable)
	float GetMaxZoomScale() const { return MaxZoomScale; }

	UFUNCTION(BlueprintCallable)
	void SetMaxZoomScale(float InMaxZoomScale);

	UFUNCTION(BlueprintCallable)
	float GetDragDeltaDecreasePower() const { return DragDeltaDecreasePower; }

	UFUNCTION(BlueprintCallable)
	void SetDragDeltaDecreasePower(float InValue) { DragDeltaDecreasePower = InValue; }

	UFUNCTION(BlueprintCallable)
	float GetZoomDeltaDecreasePower() const { return ZoomDeltaDecreasePower; }

	UFUNCTION(BlueprintCallable)
	void SetZoomDeltaDecreasePower(float InValue) { DragDeltaDecreasePower = InValue; }
};
