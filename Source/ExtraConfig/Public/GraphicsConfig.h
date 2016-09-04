// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GraphicsConfig.generated.h"

UENUM(BlueprintType)        //"BlueprintType" is essential specifier
enum class EScreenMode : uint8
{
	Exclusive		UMETA(DisplayName = "Exclusive Fullscreen"),
	Borderless		UMETA(DisplayName = "Borderless Windowed"),
	Window			UMETA(DisplayName = "Windowed")
};

UENUM(BlueprintType)
enum class EQuality : uint8
{
	Off			UMETA(DisplayName = "Off"),
	Low			UMETA(DisplayName = "Low"),
	Medium		UMETA(DisplayName = "Medium"),
	High		UMETA(DisplayName = "High"),
	Ultra		UMETA(DisplayName = "Ultra")
};

USTRUCT(BlueprintType)
struct FInt2D
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	int32 Y;

	FInt2D(int32 x, int32 y) : X(x), Y(y) {}

	FInt2D(uint32 x, uint32 y) : X(x), Y(y) {}

	FInt2D() {}
};

USTRUCT(BlueprintType)
struct FGraphicsSettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	bool VSync;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	int32 Anisotropic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	EQuality Antialiasing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	EQuality Shadows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	EQuality SSAO;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	EQuality Reflections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	EQuality MotionBlur;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	EQuality LensFlare;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	EQuality Bloom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics|Structs")
	bool SimpleLighting;
		
};

/**
 * 
 */
UCLASS(Blueprintable, Config = Game)
class UGraphicsConfig : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetResolution(int32 width, int32 height);

	UFUNCTION(BlueprintPure, Category = "Graphics")
	static FInt2D GetCurrentResolution();

	UFUNCTION(BlueprintPure, Category = "Graphics")
	static FInt2D GetDefaultResolution();

	UFUNCTION(BlueprintPure, Category = "Graphics")
	static TArray<FInt2D> GetValidResolutions();

	UFUNCTION(BlueprintPure, Category = "Graphics")
	static EScreenMode GetScreenMode();

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetScreenMode(EScreenMode mode);

	UFUNCTION(BlueprintPure, Category = "Graphics")
	static EQuality GetGraphicsPreset();

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetGraphicsPreset(EQuality level);

	UFUNCTION(BlueprintPure, Category = "Graphics")
	static FGraphicsSettings GetGraphicsSettings();

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void ToggleVSync(bool vSync);

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetAnisotropic(int32 af);

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetAntialiasing(EQuality aa);

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetShadowQuality(EQuality shadow);

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetAmbientOcclusion(EQuality ao);

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetReflections(EQuality ssr);

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetMotionBlur(EQuality blur);

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetLensFlare(EQuality lensFlare);

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void SetBloom(EQuality bloom);

	UFUNCTION(BlueprintCallable, Category = "Graphics")
	static void ToggleSimpleLighting(bool simple);
};
