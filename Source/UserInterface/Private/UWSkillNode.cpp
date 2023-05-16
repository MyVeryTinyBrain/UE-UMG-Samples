// Fill out your copyright notice in the Description page of Project Settings.


#include "UWSkillNode.h"
#include <Components/Button.h>
#include <Components/Image.h>

#include <NiagaraSystemWidget.h>

void UUWSkillNode::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnClicked.AddDynamic(this, &UUWSkillNode::Internal_OnClicked);
	Button->OnPressed.AddDynamic(this, &UUWSkillNode::Internal_OnPressed);
	Button->OnReleased.AddDynamic(this, &UUWSkillNode::Internal_OnReleased);
	Button->OnHovered.AddDynamic(this, &UUWSkillNode::Internal_OnHovered);
	Button->OnUnhovered.AddDynamic(this, &UUWSkillNode::Internal_OnUnhovered);
}

void UUWSkillNode::NativePreConstruct()
{
	Super::NativePreConstruct();
	Update();
}

void UUWSkillNode::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsPressing)
	{
		CurrentPressAccumulation += InDeltaTime;

		Internal_OnPressing();

		if (CurrentPressAccumulation >= InteractPressTime)
		{
			Internal_OnInteract();
		}
	}
}

void UUWSkillNode::Internal_OnClicked()
{
	OnClicked.Broadcast(this, IsInteractibleState());
}

void UUWSkillNode::Internal_OnPressed()
{
	OnPressed.Broadcast(this, IsInteractibleState());

	if (!IsInteractibleState())
		return;

	bIsPressing = true;
	CurrentPressAccumulation = 0.0f;
}

void UUWSkillNode::Internal_OnReleased()
{
	OnReleased.Broadcast(this, IsInteractibleState());

	if (!IsInteractibleState())
		return;

	ResetPressingState();
}

void UUWSkillNode::Internal_OnHovered()
{
	OnHovered.Broadcast(this, IsInteractibleState());
}

void UUWSkillNode::Internal_OnUnhovered()
{
	OnUnhovered.Broadcast(this, IsInteractibleState());
}

void UUWSkillNode::Internal_OnPressing()
{
	OnPressing.Broadcast(this, GetRatio());
}

void UUWSkillNode::Internal_OnInteract()
{
	OnInteract.Broadcast(this);
	
	if (bUnlocked)
		return;

	ResetPressingState();

	NSW_UnlockEffect->ActivateSystem(true);

	bUnlocked = true;
	Update();
}

void UUWSkillNode::Update()
{
	// Set skill data
	bHasSkillData = false;
	if (SkillDataTable)
	{
		bHasSkillData = FSkillData::FindSkillData(SkillDataTable, RowName, SkillData);
	}

	// Set button image
	UTexture2D* UsingSKillTexture = DefaultSkillTexture;
	if (bHasSkillData && SkillData.SkillTexture)
	{
		UsingSKillTexture = SkillData.SkillTexture;	
	}
	Img_Icon->SetBrushFromTexture(UsingSKillTexture);

	// Set button color
	Img_Out->SetColorAndOpacity(UnlockedColor);

	// Set button style
	FButtonStyle ButtonStyle = Button->WidgetStyle;
	if (bUnlocked)
	{
		Img_In->SetColorAndOpacity(UnlockedColor);
		Img_Icon->SetColorAndOpacity(LockedColor);
		
		ButtonStyle.NormalForeground = UnlockedNormalForeground;
		ButtonStyle.HoveredForeground = UnlockedHoverForeground;
		ButtonStyle.PressedForeground = UnlockedPressedForeground;

		NSW_UnlockedEffect->ActivateSystem(true);
	}
	else
	{
		Img_In->SetColorAndOpacity(LockedColor);
		Img_Icon->SetColorAndOpacity(UnlockedColor);

		ButtonStyle.NormalForeground = NormalForeground;
		ButtonStyle.HoveredForeground = HoverForeground;
		ButtonStyle.PressedForeground = PressedForeground;

		NSW_UnlockedEffect->DeactivateSystem();
	}
	Button->SetStyle(ButtonStyle);
}

void UUWSkillNode::ResetPressingState()
{
	bIsPressing = false;
	CurrentPressAccumulation = 0.0f;
}

float UUWSkillNode::GetRatio() const
{
	if (InteractPressTime == 0)
	{
		if (bIsPressing)
			return 1.0f;
		else
			return 0.0f;
	}
	return FMath::Clamp(CurrentPressAccumulation / InteractPressTime, 0.0f, 1.0f);
}

bool UUWSkillNode::IsInteractibleState() const
{
	if (bUnlocked)
	{
		return false;
	}
	else if (ParentNode && !ParentNode->bUnlocked)
	{
		return false;
	}
	return true;
}

void UUWSkillNode::SetSkillDataTable(UDataTable* InSkillDataTable)
{
	SkillDataTable = InSkillDataTable;
	Update();
}

void UUWSkillNode::SetLockedColor(const FLinearColor& InLockedColor)
{
	LockedColor = InLockedColor; 
	Update();
}

void UUWSkillNode::SetUnlockedColor(const FLinearColor& InUnlockedColor)
{
	UnlockedColor = InUnlockedColor;
	Update();
}

void UUWSkillNode::SetNormalForeground(const FLinearColor& InNormalForeground)
{
	NormalForeground = InNormalForeground;
	Update();
}

void UUWSkillNode::SetHoverForeground(const FLinearColor& InHoverForeground)
{
	HoverForeground = InHoverForeground;
	Update();
}

void UUWSkillNode::SetPressedForeground(const FLinearColor& InPressedForeground)
{
	PressedForeground = InPressedForeground;
	Update();
}

void UUWSkillNode::SetUnlockedNormalForeground(const FLinearColor& InUnlockedNormalForeground)
{
	UnlockedNormalForeground = InUnlockedNormalForeground;
	Update();
}

void UUWSkillNode::SetUnlockedHoverForeground(const FLinearColor& InUnlockedHoverForeground)
{
	UnlockedHoverForeground = InUnlockedHoverForeground;
	Update();
}

void UUWSkillNode::SetUnlockedPressedForeground(const FLinearColor& InUnlockedPressedForeground)
{
	UnlockedPressedForeground = InUnlockedPressedForeground;
	Update();
}

void UUWSkillNode::SetRowName(const FName& InRowName)
{
	RowName = InRowName;
	Update();
}

void UUWSkillNode::SetDefaultSkillTexture(UTexture2D* InDefaultSkillTexture)
{
	DefaultSkillTexture = InDefaultSkillTexture;
	Update();
}

void UUWSkillNode::SetParentNode(UUWSkillNode* InParentNode)
{
	ParentNode = InParentNode;
	Update();
}

void UUWSkillNode::SetUnlocked(bool InUnlocked)
{
	bUnlocked = InUnlocked;

	if (!bUnlocked)
	{
		ResetPressingState();
	}

	Update();
}

void UUWSkillNode::SetInteractPressTime(float InInteractPressTime)
{
	InteractPressTime = InInteractPressTime;
}
