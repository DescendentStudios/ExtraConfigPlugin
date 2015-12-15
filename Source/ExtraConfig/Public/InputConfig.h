// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/InputSettings.h"
#include "InputConfig.generated.h"

USTRUCT(BlueprintType)
struct FActionMap
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	FName ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	bool Shift;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	bool Ctrl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	bool Alt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	bool Cmd;

	FActionMap(FName actionName, FKey key, bool shift, bool ctrl, bool alt, bool cmd) :
		ActionName(actionName), Key(key), Shift(shift), Ctrl(ctrl), Alt(alt), Cmd(cmd)
	{}

	FActionMap() {}
};

USTRUCT(BlueprintType)
struct FAxisMap
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	FName AxisName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	float Scale;

	FAxisMap(FName axisName, FKey key, float scale) : AxisName(axisName), Key(key), Scale(scale)
	{}

	FAxisMap() {}
};

USTRUCT(BlueprintType)
struct FAnalogConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	bool Invert;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	float DeadZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	float Exponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Keybinding|Structs")
	float Multiplier;

	FAnalogConfig(FKey key, bool invert, float deadZone, float exp, float mult) :
		Key(key), Invert(invert), DeadZone(deadZone), Exponent(exp), Multiplier(mult)
	{}

	FAnalogConfig() {}
};

/**
 * 
 */
UCLASS()
class UInputConfig : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:	

	//Action Maps
	UFUNCTION(BlueprintCallable, Category = "Keybinding|Action")
	static bool AddActionMapping(FName actionName, FKey newKey, bool ctrl, bool shift, bool alt, bool cmd);

	UFUNCTION(BlueprintCallable, Category = "Keybinding|Action")
	static bool RemoveActionMapping(FName actionName, FKey oldKey, bool ctrl, bool shift, bool alt, bool cmd);

	UFUNCTION(BlueprintCallable, Category = "Keybinding|Action")
	static bool ModifyActionMapping(FName actionName, FKey key, bool ctrl, bool shift, bool alt, bool cmd);

	UFUNCTION(BlueprintPure, Category = "Keybinding|Action")
	static TArray<FName> GetActionNames();

	UFUNCTION(BlueprintPure, Category = "Keybinding|Action")
	static TArray<FActionMap> GetKeysForAction(FName actionName);

	//Axis Maps
	UFUNCTION(BlueprintCallable, Category = "Keybinding|Axis")
	static bool AddAxisMapping(FName axisName, FKey newKey, float scale);

	UFUNCTION(BlueprintCallable, Category = "Keybinding|Axis")
	static bool RemoveAxisMapping(FName axisName, FKey oldKey, float scale);

	UFUNCTION(BlueprintCallable, Category = "Keybinding|Axis")
	static bool ModifyAxisMapping(FName axisName, FKey key, float scale);

	UFUNCTION(BlueprintPure, Category = "Keybinding|Axis")
	static TArray<FName> GetAxisNames();

	UFUNCTION(BlueprintPure, Category = "Keybinding|Axis")
	static TArray<FAxisMap> GetKeysForAxis(FName axisName);

	//Axis Config
	UFUNCTION(BlueprintCallable, Category = "Keybinding|Config")
	static bool AddAnalogConfig(FKey axisKey, bool invert, float deadZone, float sensitivity, float exponent);

	UFUNCTION(BlueprintCallable, Category = "Keybinding|Config")
	static bool RemoveAnalogConfig(FKey axisKey);

	UFUNCTION(BlueprintCallable, Category = "Keybinding|Config")
	static bool ModifyAnalogConfig(FKey axisKey, bool invert, float deadZone, float sensitivity, float exponent);

	UFUNCTION(BlueprintPure, Category = "Keybinding|Config")
	static TArray<FKey> GetAnalogKeys();

	UFUNCTION(BlueprintPure, Category = "Keybinding|Config")
	static FAnalogConfig GetConfigForAnalog(FKey key);

	//Utility
	UFUNCTION(BlueprintCallable, Category = "Keybinding|Utility")
	static void SaveChanges();

	UFUNCTION(BlueprintCallable, Category = "Keybinding|Utility")
	static void DiscardChanges();

	UFUNCTION(BlueprintPure, Category = "Keybinding|Utility")
	static bool IsDoubleBound(FKey key, FName requestedBind);
};
