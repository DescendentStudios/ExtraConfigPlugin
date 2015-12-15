// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtraConfigPrivatePCH.h"
#include "GraphicsConfig.h"
#include "GameFramework/GameUserSettings.h"
#include "Runtime/Core/Public/Misc/ConfigCacheIni.h"
#include "Engine.h"
#include "RHI.h"

UGraphicsConfig::UGraphicsConfig(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGraphicsConfig::SetResolution(int32 width, int32 height)
{
	UGameUserSettings* settings = GEngine->GameUserSettings;

	FIntPoint res(width, height);

	settings->SetScreenResolution(res);

	settings->ApplyResolutionSettings(false);

	settings->SaveSettings();
}

FInt2D UGraphicsConfig::GetCurrentResolution()
{
	UGameUserSettings* settings = GEngine->GameUserSettings;

	FIntPoint res = settings->GetScreenResolution();

	return FInt2D(res.X, res.Y);
}

FInt2D UGraphicsConfig::GetDefaultResolution()
{
	FIntPoint res = UGameUserSettings::GetDefaultResolution();

	return FInt2D(res.X, res.Y);
}

TArray<FInt2D> UGraphicsConfig::GetValidResolutions()
{
	FScreenResolutionArray resolutions;
	TArray<FInt2D> outResolutions;

	RHIGetAvailableResolutions(resolutions, true);

	for (const FScreenResolutionRHI& res : resolutions)
	{
		FInt2D outRes;
		outRes.X = res.Width;
		outRes.Y = res.Height;
		outResolutions.Add(outRes);
	}

	return outResolutions;
}

EScreenMode UGraphicsConfig::GetScreenMode()
{
	UGameUserSettings* settings = GEngine->GameUserSettings;

	EWindowMode::Type inMode = settings->GetFullscreenMode();

	switch (inMode)
	{
	case EWindowMode::Fullscreen:
		return EScreenMode::Exclusive;
		break;
	case EWindowMode::WindowedFullscreen:
		return EScreenMode::Borderless;
		break;
	case EWindowMode::Windowed:
		return EScreenMode::Window;
		break;
	default:
		return EScreenMode::Exclusive;
	}
}

void UGraphicsConfig::SetScreenMode(EScreenMode mode)
{
	UGameUserSettings* settings = GEngine->GameUserSettings;

	EWindowMode::Type outMode;

	switch (mode)
	{
	default:
	case EScreenMode::Exclusive:
		outMode = EWindowMode::Fullscreen;
		break;
	case EScreenMode::Borderless:
		outMode = EWindowMode::WindowedFullscreen;
		break;
	case EScreenMode::Window:
		outMode = EWindowMode::Windowed;
		break;
	}

	settings->SetFullscreenMode(outMode);

	settings->ApplyResolutionSettings(false);

	settings->SaveSettings();
}

EQuality UGraphicsConfig::GetGraphicsPreset()
{
	FString value;
	GConfig->GetString(TEXT("Graphics"), TEXT("QualityPreset"), value, GGameIni);

	if (value == "Low")
	{
		return EQuality::Low;
	}
	else if (value == "High")
	{
		return EQuality::High;
	}
	else if (value == "Ultra")
	{
		return EQuality::Ultra;
	}
	else if (value == "Medium")
	{
		return EQuality::Medium;
	}
	else //custom
	{
		return EQuality::Off;
	}
}

void UGraphicsConfig::SetGraphicsPreset(EQuality level)
{
	FString value;

	switch (level)
	{
	case EQuality::Low:
		value = "Low";
		break;
	default:
	case EQuality::Medium:
		value = "Medium";
		break;
	case EQuality::High:
		value = "High";
		break;
	case EQuality::Ultra:
		value = "Ultra";
		break;
	case EQuality::Off:
		value = "Custom";
	}

	GConfig->SetString(TEXT("Graphics"), TEXT("QualityPreset"), *value, GGameIni);

	GConfig->Flush(false, GGameIni);
}

FGraphicsSettings UGraphicsConfig::GetGraphicsSettings()
{
	FGraphicsSettings output;
	int value;
	bool bVal;

	//Get VSync toggle
	GConfig->GetBool(TEXT("ConsoleVariables"), TEXT("r.VSync"), bVal, GEngineIni);
	if (bVal)
	{
		output.VSync = 1;
	}
	else
	{
		output.VSync = 0;
	}

	GConfig->GetInt(TEXT("ConsoleVariables"), TEXT("r.MaxAnisotropy"), value, GEngineIni);
	output.Anisotropic = value;

	GConfig->GetInt(TEXT("ConsoleVariables"), TEXT("r.PostProcessAAQuality"), value, GEngineIni);
	switch (value)
	{
	case 0:
	default:
		output.Antialiasing = EQuality::Off;
		break;
	case 1:
		output.Antialiasing = EQuality::Low;
		break;
	case 2:
		output.Antialiasing = EQuality::Medium;
		break;
	case 3:
		output.Antialiasing = EQuality::High;
		break;
	case 4:
		output.Antialiasing = EQuality::Ultra;
	}

	GConfig->GetInt(TEXT("ConsoleVariables"), TEXT("sg.ShadowQuality"), value, GEngineIni);
	switch (value)
	{
	case 0:
	default:
		output.Shadows = EQuality::Off;
		break;
	case 1:
		output.Shadows = EQuality::Low;
		break;
	case 2:
		output.Shadows = EQuality::Medium;
		break;
	case 3:
		output.Shadows = EQuality::High;
	}

	GConfig->GetInt(TEXT("ConsoleVariables"), TEXT("r.AmbientOcclusionLevels"), value, GEngineIni);
	switch (value)
	{
	case 0:
	default:
		output.SSAO = EQuality::Off;
		break;
	case 1:
		output.SSAO = EQuality::Low;
		break;
	case 2:
		output.SSAO = EQuality::Medium;
		break;
	case 3:
		output.SSAO = EQuality::High;
	}

	GConfig->GetInt(TEXT("ConsoleVariables"), TEXT("r.SSR.Quality"), value, GEngineIni);
	switch (value)
	{
	case 0:
	default:
		output.Reflections = EQuality::Off;
		break;
	case 1:
		output.Reflections = EQuality::Low;
		break;
	case 2:
		output.Reflections = EQuality::Medium;
		break;
	case 3:
		output.Reflections = EQuality::High;
	}

	GConfig->GetInt(TEXT("ConsoleVariables"), TEXT("r.MotionBlurQuality"), value, GEngineIni);
	switch (value)
	{
	case 0:
	default:
		output.MotionBlur = EQuality::Off;
		break;
	case 1:
		output.MotionBlur = EQuality::Low;
		break;
	case 2:
		output.MotionBlur = EQuality::Medium;
		break;
	case 3:
		output.MotionBlur = EQuality::High;
	}

	GConfig->GetInt(TEXT("ConsoleVariables"), TEXT("r.LensFlareQuality"), value, GEngineIni);
	switch (value)
	{
	case 0:
	default:
		output.LensFlare = EQuality::Off;
		break;
	case 1:
		output.LensFlare = EQuality::Low;
		break;
	case 2:
		output.LensFlare = EQuality::Medium;
		break;
	case 3:
		output.LensFlare = EQuality::High;
	}

	GConfig->GetInt(TEXT("ConsoleVariables"), TEXT("r.BloomQuality"), value, GEngineIni);
	switch (value)
	{
	case 0:
	default:
		output.Bloom = EQuality::Off;
		break;
	case 1:
		output.Bloom = EQuality::Low;
		break;
	case 2:
		output.Bloom = EQuality::Medium;
		break;
	case 3:
		output.Bloom = EQuality::High;
		break;
	case 4:
		output.Bloom = EQuality::Ultra;
	}

	GConfig->GetBool(TEXT("ConsoleVariables"), TEXT("r.SimpleDynamicLighting"), bVal, GEngineIni);
	if (bVal)
	{
		output.SimpleLighting = 1;
	}
	else
	{
		output.SimpleLighting = 0;
	}

	return output;
}

void UGraphicsConfig::ToggleVSync(bool vSync)
{
	int32 intVSync;

	if (vSync)
	{
		intVSync = 1;
	}
	else
	{
		intVSync = 0;
	}

	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("r.VSync"), intVSync, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}

void UGraphicsConfig::SetAnisotropic(int32 af)
{
	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("r.MaxAnisotropy"), af, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}

void UGraphicsConfig::SetAntialiasing(EQuality aa)
{
	int32 intAA;

	switch (aa)
	{
	case EQuality::Off:
		intAA = 0;
		break;
	case EQuality::Low:
		intAA = 1;
		break;
	case EQuality::Medium:
		intAA = 2;
		break;
	default:
	case EQuality::High:
		intAA = 3;
		break;
	case EQuality::Ultra:
		intAA = 4;
	}

	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("r.PostProcessAAQuality"), intAA, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}

void UGraphicsConfig::SetShadowQuality(EQuality shadow)
{
	int32 intShadow;

	switch (shadow)
	{
	case EQuality::Off:
		intShadow = 0;
		break;
	case EQuality::Low:
		intShadow = 1;
		break;
	default:
	case EQuality::Medium:
		intShadow = 2;
		break;
	case EQuality::High:
		intShadow = 3;
	}

	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("sg.ShadowQuality"), intShadow, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}

void UGraphicsConfig::SetAmbientOcclusion(EQuality ao)
{
	int32 intAO;

	switch (ao)
	{
	case EQuality::Off:
		intAO = 0;
		break;
	case EQuality::Low:
		intAO = 1;
		break;
	default:
	case EQuality::Medium:
		intAO = 2;
		break;
	case EQuality::High:
		intAO = 3;
	}

	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("r.AmbientOcclusionLevels"), intAO, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}

void UGraphicsConfig::SetReflections(EQuality ssr)
{
	int32 intSSR;

	switch (ssr)
	{
	case EQuality::Off:
		intSSR = 0;
		break;
	case EQuality::Low:
		intSSR = 1;
		break;
	default:
	case EQuality::Medium:
		intSSR = 2;
		break;
	case EQuality::High:
		intSSR = 3;
	}

	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("r.SSR.Quality"), intSSR, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}

void UGraphicsConfig::SetMotionBlur(EQuality blur)
{
	int32 intBlur;

	switch (blur)
	{
	default:
	case EQuality::Off:
		intBlur = 0;
		break;
	case EQuality::Low:
		intBlur = 1;
		break;
	case EQuality::Medium:
		intBlur = 2;
		break;
	case EQuality::High:
		intBlur = 3;
	}

	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("r.MotionBlurQuality"), intBlur, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}

void UGraphicsConfig::SetLensFlare(EQuality lensFlare)
{
	int32 intFlare;

	switch (lensFlare)
	{
	default:
	case EQuality::Off:
		intFlare = 0;
		break;
	case EQuality::Low:
		intFlare = 1;
		break;
	case EQuality::Medium:
		intFlare = 2;
		break;
	case EQuality::High:
		intFlare = 3;
	}

	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("r.LensFlareQuality"), intFlare, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}

void UGraphicsConfig::SetBloom(EQuality bloom)
{
	int32 intBloom;

	switch (bloom)
	{
	default:
	case EQuality::Off:
		intBloom = 0;
		break;
	case EQuality::Low:
		intBloom = 1;
		break;
	case EQuality::Medium:
		intBloom = 2;
		break;
	case EQuality::High:
		intBloom = 3;
		break;
	case EQuality::Ultra:
		intBloom = 4;
	}

	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("r.BloomQuality"), intBloom, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}

void UGraphicsConfig::ToggleSimpleLighting(bool simple)
{
	int32 intSimple;

	if (simple)
	{
		intSimple = 1;
	}
	else
	{
		intSimple = 0;
	}

	GConfig->SetInt(TEXT("ConsoleVariables"), TEXT("r.SimpleDynamicLighting"), intSimple, GEngineIni);

	GConfig->Flush(false, GEngineIni);
}
