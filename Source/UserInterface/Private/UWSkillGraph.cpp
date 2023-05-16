// Fill out your copyright notice in the Description page of Project Settings.


#include "UWSkillGraph.h"
#include <Components/PanelWidget.h>
#include "UWGradient3Line.h"
#include <Components/CanvasPanelSlot.h>
#include <UserData.h>

void UUWSkillGraph::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUWSkillGraph::NativePreConstruct()
{
	Super::NativePreConstruct();

	ApplyNodeSettings();
	ApplyLineSettings();
	RecalculateNodeArea();
	ReconnectLines();
}

void UUWSkillGraph::OnSkillNodeReleased(UUWSkillNode* SkillNode, bool IsInteractible)
{
	if (IsInteractible)
		SetLineVariablesByRatio(SkillNode, 0);
}

void UUWSkillGraph::OnSkillNodePressing(UUWSkillNode* SkillNode, float Ratio)
{
	SetLineVariablesByRatio(SkillNode, Ratio);
}

void UUWSkillGraph::OnSkillNodeInteract(UUWSkillNode* SkillNode)
{
	SetLineVariablesByRatio(SkillNode, 1);

	if (UserData)
	{
		FSkillArray& UnlcokedSkills = UserData->UnlockedSkills.FindOrAdd(HeroType);
		UnlcokedSkills.Array.Add(SkillNode->GetSkillData());
	}
}

void UUWSkillGraph::Internal_OnSkillNodeHovered(UUWSkillNode* SkillNode, bool IsInteractible)
{
	OnSkillNodeHovered.Broadcast(SkillNode, IsInteractible);
}

void UUWSkillGraph::Internal_OnSkillNodeUnhovered(UUWSkillNode* SkillNode, bool IsInteractible)
{
	OnSkillNodeUnhovered.Broadcast(SkillNode, IsInteractible);
}

UUWGradient3Line* UUWSkillGraph::AddLine(UUWSkillNode* Start, UUWSkillNode* End)
{
	UUWGradient3Line* element = CreateWidget<UUWGradient3Line>(Canv_Lines, LineTemplate);

	if (!element)
	{
		FString Position = (FString(__FUNCTION__) + FString(TEXT(": ")) + FString::FromInt(__LINE__));
		UE_LOG(LogTemp, Error, TEXT("Type missmatch %s"), *Position);
		return nullptr;
	}

	Canv_Lines->AddChild(element);
	ConnectLines.Add(element);

	element->SetStartTarget(Start);
	element->SetEndTarget(End);
	element->SetLineWidht(LineWidht);

	UCanvasPanelSlot* elementCanvasPanelSlot = Cast<UCanvasPanelSlot>(element->Slot);
	if (elementCanvasPanelSlot)
	{
		elementCanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		elementCanvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
	}

	return element;
}

TArray<UUWGradient3Line*> UUWSkillGraph::GetLine(UUWSkillNode* End) const
{
	TArray<UUWGradient3Line*> Results;
	for (UUWGradient3Line* Line : ConnectLines)
	{
		if (Line->GetEndTarget() == End)
			Results.Add(Line);
	}
	return Results;
}

void UUWSkillGraph::SetLineVariablesByRatio(UUWSkillNode* SkillNode, float Ratio)
{
	TArray<UUWGradient3Line*> Lines = GetLine(SkillNode);
	for (UUWGradient3Line* Line : Lines)
	{
		float LineMidRatio = MidRatio + (1.0f - MidRatio) * Ratio;
		Line->SetMidRatio(LineMidRatio);

		float PowRatio = FMath::Pow(Ratio, 2.0f);
		FLinearColor LineMidColor = FMath::Lerp(MidColor, StartColor, PowRatio);
		Line->SetMidColor(LineMidColor);
	}
}

void UUWSkillGraph::ApplyNodeSettings()
{
	// Apply settings to nodes
	TArray<UWidget*> Childrens = Canv_Nodes->GetAllChildren();
	SkillNodes.Empty();
	for (UWidget* Child : Childrens)
	{
		UUWSkillNode* SkillNode = Cast<UUWSkillNode>(Child);
		if (!SkillNode)
			continue;

		if (!SkillNode->OnReleased.IsAlreadyBound(this, &UUWSkillGraph::OnSkillNodeReleased))
			SkillNode->OnReleased.AddDynamic(this, &UUWSkillGraph::OnSkillNodeReleased);

		if (!SkillNode->OnPressing.IsAlreadyBound(this, &UUWSkillGraph::OnSkillNodePressing))
			SkillNode->OnPressing.AddDynamic(this, &UUWSkillGraph::OnSkillNodePressing);
		
		if (!SkillNode->OnInteract.IsAlreadyBound(this, &UUWSkillGraph::OnSkillNodeInteract))
			SkillNode->OnInteract.AddDynamic(this, &UUWSkillGraph::OnSkillNodeInteract);

		if (!SkillNode->OnHovered.IsAlreadyBound(this, &UUWSkillGraph::Internal_OnSkillNodeHovered))
			SkillNode->OnHovered.AddDynamic(this, &UUWSkillGraph::Internal_OnSkillNodeHovered);

		if (!SkillNode->OnUnhovered.IsAlreadyBound(this, &UUWSkillGraph::Internal_OnSkillNodeUnhovered))
			SkillNode->OnUnhovered.AddDynamic(this, &UUWSkillGraph::Internal_OnSkillNodeUnhovered);
		
		SkillNode->SetInteractPressTime(InteractPressTime);

		if (UserData)
		{
			FSkillArray* UnlcokedSkills = UserData->UnlockedSkills.Find(HeroType);
			if (UnlcokedSkills)
			{
				SkillNode->SetUnlocked(UnlcokedSkills->Array.Contains(SkillNode->GetSkillData()));
			}
		}

		if (SkillDataTable)
		{
			SkillNode->SetSkillDataTable(SkillDataTable);
		}

		SkillNodes.Add(SkillNode);
	}

	if (RootSkillNode)
	{
		RootSkillNode->SetUnlocked(true);
	}
}

void UUWSkillGraph::ApplyLineSettings()
{
	for (UUWGradient3Line* Line : ConnectLines)
	{
		Line->SetStartColor(StartColor);
		Line->SetMidColor(MidColor);
		Line->SetEndColor(EndColor);
		Line->SetStartRatio(StartRatio);
		Line->SetMidRatio(MidRatio);
		Line->SetEndRatio(EndRatio);
		Line->SetLineWidht(LineWidht);
	}
}

void UUWSkillGraph::Setup(UUserData* InUserData, class UDataTable* InSkillDataTable, EHeroType InHeroType)
{
	UserData = InUserData;
	SkillDataTable = InSkillDataTable;
	HeroType = InHeroType;
	ApplyNodeSettings();
}

void UUWSkillGraph::SetUserData(UUserData* InUserData)
{
	UserData = InUserData;
	ApplyNodeSettings();
}

void UUWSkillGraph::SetSkillDataTable(UDataTable* InSkillDataTable)
{
	SkillDataTable = InSkillDataTable;
	ApplyNodeSettings();
}

void UUWSkillGraph::SetHeroType(EHeroType InHeroType)
{
	HeroType = InHeroType;
	ApplyNodeSettings();
}

void UUWSkillGraph::RecalculateNodeArea()
{
	const FVector2D MinVector2D = FVector2D(FLT_MIN, FLT_MIN);
	const FVector2D MaxVector2D = FVector2D(FLT_MAX, FLT_MAX);
	FVector2D Min = MaxVector2D;
	FVector2D Max = MinVector2D;

	for (UUWSkillNode* Node : SkillNodes)
	{
		UCanvasPanelSlot* nodeCanvasPanelSlot = Cast<UCanvasPanelSlot>(Node->Slot);
		if (nodeCanvasPanelSlot)
		{
			FVector2D NodePos = nodeCanvasPanelSlot->GetPosition();
			FVector2D NodeSize = nodeCanvasPanelSlot->GetSize();
			FVector2D NodeMin = NodePos - NodeSize * 0.5f;
			FVector2D NodeMax = NodePos + NodeSize * 0.5f;

			Min.X = FMath::Min(Min.X, NodeMin.X);
			Min.Y = FMath::Min(Min.Y, NodeMin.Y);
			Max.X = FMath::Max(Max.X, NodeMax.X);
			Max.Y = FMath::Max(Max.Y, NodeMax.Y);
		}
	}

	if (Min == MaxVector2D || Max == MinVector2D)
	{
		Min = Max = FVector2D::ZeroVector;
	}
	else
	{
		FVector2D ExtraSize = FVector2D(SizableExtraSize, SizableExtraSize);
		Min -= ExtraSize * 0.5f;
		Max += ExtraSize * 0.5f;
	}
	MinNodeArea = Min;
	MaxNodeArea = Max;
}

void UUWSkillGraph::ReconnectLines()
{
	Canv_Lines->ClearChildren();
	ConnectLines.Empty();
	for (UUWSkillNode* Node : SkillNodes)
	{
		if (!Node->GetParentNode())
			continue;

		AddLine(Node->GetParentNode(), Node);
	}
}

UUWSkillNode* UUWSkillGraph::GetRootSkillNode()
{
	return RootSkillNode;
}

const FVector2D& UUWSkillGraph::GetMinNodeArea()
{
	return MinNodeArea;
}

const FVector2D& UUWSkillGraph::GetMaxNodeArea()
{
	return MaxNodeArea;
}

FVector2D UUWSkillGraph::GetCenterOfNodeArea()
{
	return (MinNodeArea + MaxNodeArea) * 0.5f;
}

FVector2D UUWSkillGraph::GetNodeAreaSize()
{
	return MaxNodeArea - MinNodeArea;
}

const TArray<TObjectPtr<class UUWSkillNode>>& UUWSkillGraph::GetNodes() const
{
	return SkillNodes;
}

void UUWSkillGraph::SetSizableExtraSize(float InSizableExtraSize)
{
	SizableExtraSize = InSizableExtraSize;
	RecalculateNodeArea();
}

void UUWSkillGraph::SetStartColor(const FLinearColor& InStartColor)
{
	StartColor = InStartColor;
	ApplyLineSettings();
}

void UUWSkillGraph::SetMidColor(const FLinearColor& InMidColor)
{
	MidColor = InMidColor;
	ApplyLineSettings();
}

void UUWSkillGraph::SetEndColor(const FLinearColor& InEndColor)
{
	EndColor = InEndColor;
	ApplyLineSettings();
}

void UUWSkillGraph::SetStartRatio(float InStartRatio)
{
	StartRatio = InStartRatio;
	ApplyLineSettings();
}

void UUWSkillGraph::SetMidRatio(float InMidRatio)
{
	MidRatio = InMidRatio;
	ApplyLineSettings();
}

void UUWSkillGraph::SetEndRatio(float InEndRatio)
{
	EndRatio = InEndRatio;
	ApplyLineSettings();
}

void UUWSkillGraph::SetLineWidht(float InLineWidht)
{
	LineWidht = InLineWidht;
	ApplyLineSettings();
}

void UUWSkillGraph::SetInteractPressTime(float InInteractPressTime)
{
	InteractPressTime = InInteractPressTime;
	ApplyNodeSettings();
}
