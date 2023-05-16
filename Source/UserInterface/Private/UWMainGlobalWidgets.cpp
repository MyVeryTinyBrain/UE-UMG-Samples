// Fill out your copyright notice in the Description page of Project Settings.


#include "UWMainGlobalWidgets.h"
#include <Components/PanelWidget.h>

TObjectPtr<UUWMainGlobalWidgets> UUWMainGlobalWidgets::G_Instance = nullptr;

void UUWMainGlobalWidgets::NativeConstruct()
{
	Super::NativeConstruct();

	if (G_Instance)
	{
		UPanelWidget* Parent = G_Instance->GetParent();
		if (Parent)
		{
			Parent->RemoveChild(G_Instance);
		}
		else
		{
			G_Instance->MarkAsGarbage();
		}
		G_Instance = nullptr;
		UE_LOG(LogTemp, Error, TEXT("UUWMainGlobalWidgets Is Already exists. Removed Previous UUWMainGlobalWidgets(%s)"), *G_Instance->GetFName().ToString());
	}

	G_Instance = this;
}

void UUWMainGlobalWidgets::NativeDestruct()
{
	Super::NativeDestruct();

	if (G_Instance == this)
	{
		G_Instance = nullptr;
	}
}

void UUWMainGlobalWidgets::PushToPrevWidgetStack(UUserWidget* InWidget)
{
	PrevWidgetStack.push(InWidget);
}

void UUWMainGlobalWidgets::PopFromPrevWidgetStack()
{
	PrevWidgetStack.pop();
}

UUserWidget* UUWMainGlobalWidgets::GetTopOfPrevWidgetStack() const
{
	if (PrevWidgetStack.empty())
	{
		return nullptr;
	}

	return PrevWidgetStack.top();
}

bool UUWMainGlobalWidgets::TryPopFromPrevWidgetStack(UUserWidget* InWidget)
{
	if (GetTopOfPrevWidgetStack() == InWidget)
	{
		PopFromPrevWidgetStack();
		return true;
	}

	return false;
}
