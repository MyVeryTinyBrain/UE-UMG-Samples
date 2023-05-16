// Fill out your copyright notice in the Description page of Project Settings.


#include "UserData.h"

UUserData::UUserData()
{
	if (!DraggableItems)
	{
		DraggableItems = NewObject<UDraggableItemContainer>();
	}
}
