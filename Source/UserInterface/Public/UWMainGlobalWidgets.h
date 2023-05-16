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

	/*	���� ���� ������ Escape ��ư�� ���� ���� �������� ���ư��� ���� ���˴ϴ�.
		Escape ��ư�� ������ �� ������ �ֻ�ܿ� �ִ� ������ ��쿡�� ��ư Ŭ�� �ݹ��� ����ϱ� �����Դϴ�. */

	// � ������ �ٸ� ���� ���� ���� ��� ������ ������ ������ ����մϴ�.
	UFUNCTION(BlueprintCallable)
	void PushToPrevWidgetStack(UUserWidget* InWidget);

	UFUNCTION(BlueprintCallable)
	void PopFromPrevWidgetStack();

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetTopOfPrevWidgetStack() const;

	// � ������ ������ ������ �� �����̶�� ���� ��ȯ�ϰ� ���ÿ��� �����մϴ�.
	UFUNCTION(BlueprintCallable)
	bool TryPopFromPrevWidgetStack(UUserWidget* InWidget);
};
