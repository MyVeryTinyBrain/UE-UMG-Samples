// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWItemCount.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWItemCount : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_Title;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Txt_ItemCount;
		
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetTitle", BlueprintSetter = "SetTitle", meta = (AllowPrivateAccess))
	FText Title = FText::FromString(TEXT("Item"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetItemCount", BlueprintSetter = "SetItemCount", meta = (AllowPrivateAccess))
	int32 ItemCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetMaxItemCount", BlueprintSetter = "SetMaxItemCount", meta = (AllowPrivateAccess))
	int32 MaxItemCount = 0;

protected:
	virtual void NativePreConstruct() override;

private:
	void UpdateTitle();

public:
	UFUNCTION(BlueprintCallable)
	const FText& GetTitle() const { return Title; }

	UFUNCTION(BlueprintCallable)
	void SetTitle(const FText& InTitile);
	void SetTitle(const FString& InTitile);

	UFUNCTION(BlueprintCallable)
	int32 GetItemCount() const { return ItemCount; }
	
	UFUNCTION(BlueprintCallable)
	void SetItemCount(int32 InItemCount);

	UFUNCTION(BlueprintCallable)
	int32 GetMaxItemCount() const { return ItemCount; }

	UFUNCTION(BlueprintCallable)
	void SetMaxItemCount(int32 InMaxItemCount);
};
