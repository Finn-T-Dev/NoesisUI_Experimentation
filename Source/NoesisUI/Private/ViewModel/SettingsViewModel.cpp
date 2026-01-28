// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "ViewModel/SettingsViewModel.h"
#include "CoreMinimal.h"
#include "NoesisBaseComponent.h"


//UCLASS()
//class NOESISUI_API USettingsViewModel : public UNoesisBaseComponent
//{
//	GENERATED_BODY()
//
//private:
//	float _masterVolume = 1.0f;
//
//public:
//	UFUNCTION()
//	float GetMasterVolume() const { return _masterVolume; }
//
//	UFUNCTION()
//	void SetMasterVolume(float Value)
//	{
//		if (_masterVolume != Value)
//		{
//			_masterVolume = Value;
//
//			ApplyMasterVolume(Value);
//		}
//	}
//
//	void ApplyMasterVolume(float volume)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Master Volume changed to: %f"), volume);
//	}
//
//	NS_IMPLEMENT_INLINE_REFLECTION(USettingsViewModel, UNoesisBaseComponent)
//	{
//		NsProp("MasterVolume", &USettingsViewModel::GetMasterVolume, &USettingsViewModel::SetMasterVolume);
//	}
//};

