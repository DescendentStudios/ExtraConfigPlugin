// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtraConfigPrivatePCH.h"
#include "InputConfig.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"

UInputConfig::UInputConfig(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

// -------
// Actions
// -------

bool UInputConfig::AddActionMapping(FName actionName, FKey newKey, bool ctrl, bool shift, bool alt, bool cmd)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	FInputActionKeyMapping newAction(actionName, newKey, shift, ctrl, alt, cmd);

	Settings->AddActionMapping(newAction);

	return true;
}

bool UInputConfig::RemoveActionMapping(FName actionName, FKey oldKey, bool ctrl, bool shift, bool alt, bool cmd)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	FInputActionKeyMapping oldAction(actionName, oldKey, shift, ctrl, alt, cmd);

	Settings->RemoveActionMapping(oldAction);

	return true;
}

bool UInputConfig::ModifyActionMapping(FName actionName, FKey key, bool ctrl, bool shift, bool alt, bool cmd)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	for (auto& actionMap : Settings->ActionMappings)
	{
		if (actionMap.ActionName == actionName && actionMap.Key == key)
		{
			actionMap.bCtrl = ctrl;
			actionMap.bShift = shift;
			actionMap.bAlt = alt;
			actionMap.bCmd = cmd;

			return true;
		}
	}

	return false;
}

TArray<FName> UInputConfig::GetActionNames()
{
	TArray<FName> tempActions;
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (Settings)
	{
		Settings->GetActionNames(tempActions);
	}
	return tempActions;
}

TArray<FActionMap> UInputConfig::GetKeysForAction(FName actionName)
{
	TArray<FActionMap> maps;

	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return TArray<FActionMap>();

	for (auto actionMap : Settings->ActionMappings)
	{
		if (actionMap.ActionName == actionName)
		{
			maps.Add(FActionMap(actionMap.ActionName, actionMap.Key, actionMap.bShift, actionMap.bCtrl, actionMap.bAlt, actionMap.bCmd));
		}
	}

	return maps;
}

// ----
// Axis
// ----

bool UInputConfig::AddAxisMapping(FName axisName, FKey newKey, float scale)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	FInputAxisKeyMapping newAxis(axisName, newKey, scale);

	Settings->AddAxisMapping(newAxis);

	return true;
}

bool UInputConfig::RemoveAxisMapping(FName axisName, FKey oldKey, float scale)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	FInputAxisKeyMapping oldAxis(axisName, oldKey, scale);

	TArray<FInputAxisKeyMapping> tempMaps(Settings->AxisMappings);
	
	Settings->RemoveAxisMapping(oldAxis);

	return true;
}

bool UInputConfig::ModifyAxisMapping(FName axisName, FKey key, float scale)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	for (auto& axisMap : Settings->AxisMappings)
	{
		if (axisMap.AxisName == axisName && axisMap.Key == key)
		{
			axisMap.Scale = scale;
			return true;
		}
	}

	return false;
}

TArray<FName> UInputConfig::GetAxisNames()
{
	TArray<FName> tempAxes;
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (Settings)
	{
		Settings->GetAxisNames(tempAxes);
	}
	return tempAxes;
}

TArray<FAxisMap> UInputConfig::GetKeysForAxis(FName axisName)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return TArray<FAxisMap>();

	TArray<FAxisMap> maps;

	for (auto axisMap : Settings->AxisMappings)
	{
		if (axisMap.AxisName == axisName)
		{
			maps.Add(FAxisMap(axisMap.AxisName, axisMap.Key, axisMap.Scale));
		}
	}

	return maps;
}

// ------
// Config
// ------

bool UInputConfig::AddAnalogConfig(FKey axisKey, bool invert, float deadZone, float sensitivity, float exponent)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	int32 idx = Settings->AxisConfig.Add(FInputAxisConfigEntry());
	FInputAxisConfigEntry& entry = Settings->AxisConfig[idx];

	entry.AxisKeyName = axisKey.GetFName();
	entry.AxisProperties.bInvert = invert;
	entry.AxisProperties.DeadZone = deadZone;
	entry.AxisProperties.Exponent = exponent;
	entry.AxisProperties.Sensitivity = sensitivity;

	return true;
}

bool UInputConfig::RemoveAnalogConfig(FKey axisKey)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	FName keyName = axisKey.GetFName();

	//have to use index here, as FInputAxisConfigEntry does not have a == operator,
	//rendering TArray<>::Remove useless.
	for (int32 i = 0; i < Settings->AxisConfig.Num(); i++)
	{
		FInputAxisConfigEntry& config = Settings->AxisConfig[i];
		if (keyName == (config.AxisKeyName))
		{
			Settings->AxisConfig.RemoveAtSwap(i);

			return true;
		}
	}

	return false;
}

bool UInputConfig::ModifyAnalogConfig(FKey axisKey, bool invert, float deadZone, float sensitivity, float exponent)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	FName keyName = axisKey.GetFName();

	for (auto& config : Settings->AxisConfig)
	{
		if (keyName == (config.AxisKeyName))
		{
			config.AxisProperties.bInvert = invert;
			config.AxisProperties.DeadZone = deadZone;
			config.AxisProperties.Exponent = exponent;
			config.AxisProperties.Sensitivity = sensitivity;
			return true;
		}
	}

	return false;
}

TArray<FKey> UInputConfig::GetAnalogKeys()
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return TArray<FKey>();

	TArray<FKey> keys;

	for (auto config : Settings->AxisConfig)
	{
		FKey key(config.AxisKeyName);
		if (!(keys.Contains(key)))
		{
			keys.Add(key);
		}
	}

	return keys;
}

FAnalogConfig UInputConfig::GetConfigForAnalog(FKey key)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return FAnalogConfig();

	for (auto config : Settings->AxisConfig)
	{
		if ((config.AxisKeyName) == key.GetFName())
		{
			bool invert = config.AxisProperties.bInvert;
			float dz = config.AxisProperties.DeadZone;
			float exp = config.AxisProperties.Exponent;
			float mult = config.AxisProperties.Sensitivity;

			return FAnalogConfig(key, invert, dz, exp, mult);
		}
	}

	return FAnalogConfig();
}

// -------
// Utility
// -------

void UInputConfig::SaveChanges()
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	Settings->SaveConfig();

	//REBUILDS INPUT, creates modified config in Saved/Config/Windows/Input.ini
	for (TObjectIterator<UPlayerInput> It; It; ++It)
	{
		It->ForceRebuildingKeyMaps(true);
	}
}

void UInputConfig::DiscardChanges()
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	Settings->ReloadConfig();
}

bool UInputConfig::IsDoubleBound(FKey key, FName requestedBind)
{
	UInputSettings* Settings = UInputSettings::StaticClass()->GetDefaultObject<UInputSettings>();
	if (!Settings) return false;

	for (auto action : Settings->ActionMappings)
	{
		if (action.ActionName != requestedBind && action.Key == key)
		{
			return true;
		}
	}

	for (auto axis : Settings->AxisMappings)
	{
		if (axis.AxisName != requestedBind && axis.Key == key)
		{
			return true;
		}
	}

	return false;
}
