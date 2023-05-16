// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <stack>
#include "Blueprint/UserWidget.h"
#include "UWMainGlobalWidgets.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWMainGlobalWidgets : public UUserWidget
{
	GENERATED_BODY()
	
	static TObjectPtr<UUWMainGlobalWidgets> G_Instance;

	UPROPERTY(meta = (BindWidget))
	class UUWButton* WBB_Escape;

	UPROPERTY(meta = (BindWidget))
	class UUWFade* WBF_Fade;

	std::stack<UUserWidget*> PrevWidgetStack;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


public:
	UFUNCTION(BlueprintCallable)
	static UUWMainGlobalWidgets* GetMainGlobalWidgets() { return G_Instance; };

	UFUNCTION(BlueprintCallable)
	class UUWButton* GetEscapeButton() const { return WBB_Escape; }

	UFUNCTION(BlueprintCallable)
	class UUWFade* GetFade() const { return WBF_Fade; }

	/*	이전 위젯 스택은 Escape 버튼을 눌러 이전 위젯으로 돌아가기 위해 사용됩니다.
		Escape 버튼이 눌렸을 때 스택의 최상단에 있는 위젯인 경우에만 버튼 클릭 콜백을 사용하기 위함입니다. */

	// 어떤 위젯이 다른 위젯 위에 덮힐 경우 덮히기 이전의 위젯을 기록합니다.
	UFUNCTION(BlueprintCallable)
	void PushToPrevWidgetStack(UUserWidget* InWidget);

	UFUNCTION(BlueprintCallable)
	void PopFromPrevWidgetStack();

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetTopOfPrevWidgetStack() const;

	// 어떤 위젯이 이전에 덮히게 된 위젯이라면 참을 반환하고 스택에서 제거합니다.
	UFUNCTION(BlueprintCallable)
	bool TryPopFromPrevWidgetStack(UUserWidget* InWidget);
};
