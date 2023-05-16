// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UWSkillNode.h"
#include "Blueprint/UserWidget.h"
#include "UWSkillGraph.generated.h"

/**
 * 
 */
UCLASS()
class USERINTERFACE_API UUWSkillGraph : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* Canv_Lines;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* Canv_Nodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUWGradient3Line> LineTemplate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<class UUWSkillNode>> SkillNodes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<TObjectPtr<class UUWGradient3Line>> ConnectLines;

	UPROPERTY(meta = (BindWidget))
	class UUWSkillNode* RootSkillNode;

	UPROPERTY()
	FVector2D MinNodeArea = FVector2D::ZeroVector;
	
	UPROPERTY()
	FVector2D MaxNodeArea = FVector2D::ZeroVector;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetUserData", BlueprintSetter = "SetUserData", meta = (AllowPrivateAccess))
	TObjectPtr<class UUserData> UserData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetSkillDataTable", BlueprintSetter = "SetSkillDataTable", meta = (AllowPrivateAccess))
	TObjectPtr<class UDataTable> SkillDataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetHeroType", BlueprintSetter = "SetHeroType", meta = (AllowPrivateAccess))
	EHeroType HeroType = EHeroType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetSizableExtraSize", BlueprintSetter = "SetSizableExtraSize", meta = (AllowPrivateAccess))
	float SizableExtraSize = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetStartColor", BlueprintSetter = "SetStartColor", meta = (AllowPrivateAccess))
	FLinearColor StartColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetMidColor", BlueprintSetter = "SetMidColor", meta = (AllowPrivateAccess))
	FLinearColor MidColor = FLinearColor(1, 1, 1, 0.1f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetEndColor", BlueprintSetter = "SetEndColor", meta = (AllowPrivateAccess))
	FLinearColor EndColor = FLinearColor(1, 1, 1, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetStartRatio", BlueprintSetter = "SetStartRatio", meta = (AllowPrivateAccess = true, UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0))
	float StartRatio = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetMidRatio", BlueprintSetter = "SetMidRatio", meta = (AllowPrivateAccess = true, UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0))
	float MidRatio = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetEndRatio", BlueprintSetter = "SetEndRatio", meta = (AllowPrivateAccess = true, UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0))
	float EndRatio = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetLineWidht", BlueprintSetter = "SetLineWidht", meta = (AllowPrivateAccess))
	float LineWidht = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = "GetInteractPressTime", BlueprintSetter = "SetInteractPressTime", meta = (AllowPrivateAccess))
	float InteractPressTime = 0.5f;

public:
	UPROPERTY(BlueprintAssignable, Category = "Node|Event")
	FOnSkillNodeHoverEvent OnSkillNodeHovered;

	UPROPERTY(BlueprintAssignable, Category = "Node|Event")
	FOnSkillNodeHoverEvent OnSkillNodeUnhovered;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION()
	virtual void OnSkillNodeReleased(class UUWSkillNode* SkillNode, bool IsInteractible);

	UFUNCTION()
	virtual void OnSkillNodePressing(class UUWSkillNode* SkillNode, float Ratio);

	UFUNCTION()
	virtual void OnSkillNodeInteract(class UUWSkillNode* SkillNode);

	UFUNCTION()
	virtual void Internal_OnSkillNodeHovered(class UUWSkillNode* SkillNode, bool IsInteractible);

	UFUNCTION()
	virtual void Internal_OnSkillNodeUnhovered(class UUWSkillNode* SkillNode, bool IsInteractible);

private:
	class UUWGradient3Line* AddLine(class UUWSkillNode* Start, class UUWSkillNode* End);
	TArray<class UUWGradient3Line*> GetLine(class UUWSkillNode* End) const;
	void SetLineVariablesByRatio(UUWSkillNode* SkillNode, float Ratio);

private:
	void ApplyNodeSettings();
	void ApplyLineSettings();

public:
	UFUNCTION(BlueprintCallable)
	void Setup(class UUserData* InUserData, class UDataTable* InSkillDataTable, EHeroType InHeroType);

	UFUNCTION(BlueprintCallable)
	class UUserData* GetUserData() const { return UserData; }

	UFUNCTION(BlueprintCallable)
	void SetUserData(class UUserData* InUserData);

	UFUNCTION(BlueprintCallable)
	class UDataTable* GetSkillDataTable() const { return SkillDataTable; }
	
	UFUNCTION(BlueprintCallable)
	void SetSkillDataTable(class UDataTable* InSkillDataTable);

	UFUNCTION(BlueprintCallable)
	EHeroType GetHeroType() const { return HeroType; }

	UFUNCTION(BlueprintCallable)
	void SetHeroType(EHeroType InHeroType);

	UFUNCTION(BlueprintCallable)
	void RecalculateNodeArea();

	UFUNCTION(BlueprintCallable)
	void ReconnectLines();

	UFUNCTION(BlueprintCallable)
	class UUWSkillNode* GetRootSkillNode();

	UFUNCTION(BlueprintCallable)
	const FVector2D& GetMinNodeArea();

	UFUNCTION(BlueprintCallable)
	const FVector2D& GetMaxNodeArea();

	UFUNCTION(BlueprintCallable)
	FVector2D GetCenterOfNodeArea();

	UFUNCTION(BlueprintCallable)
	FVector2D GetNodeAreaSize();

	UFUNCTION(BlueprintCallable)
	const TArray<TObjectPtr<class UUWSkillNode>>& GetNodes() const;

	UFUNCTION(BlueprintCallable)
	float GetSizableExtraSize() const { return SizableExtraSize; }

	UFUNCTION(BlueprintCallable)
	void SetSizableExtraSize(float InSizableExtraSize);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetStartColor() const { return StartColor; }

	UFUNCTION(BlueprintCallable)
	void SetStartColor(const FLinearColor& InStartColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetMidColor() const { return MidColor; }

	UFUNCTION(BlueprintCallable)
	void SetMidColor(const FLinearColor& InMidColor);

	UFUNCTION(BlueprintCallable)
	const FLinearColor& GetEndColor() const { return EndColor; }

	UFUNCTION(BlueprintCallable)
	void SetEndColor(const FLinearColor& InEndColor);

	UFUNCTION(BlueprintCallable)
	float GetStartRatio() const { return StartRatio; }

	UFUNCTION(BlueprintCallable)
	void SetStartRatio(float InStartRatio);

	UFUNCTION(BlueprintCallable)
	float GetMidRatio() const { return MidRatio; }

	UFUNCTION(BlueprintCallable)
	void SetMidRatio(float InMidRatio);

	UFUNCTION(BlueprintCallable)
	float GetEndRatio() const { return EndRatio; }

	UFUNCTION(BlueprintCallable)
	void SetEndRatio(float InEndRatio);

	UFUNCTION(BlueprintCallable)
	float GetLineWidht() const { return LineWidht; }

	UFUNCTION(BlueprintCallable)
	void SetLineWidht(float InLineWidht);

	UFUNCTION(BlueprintCallable)
	float GetInteractPressTime() const { return InteractPressTime; }

	UFUNCTION(BlueprintCallable)
	void SetInteractPressTime(float InInteractPressTime);
};
