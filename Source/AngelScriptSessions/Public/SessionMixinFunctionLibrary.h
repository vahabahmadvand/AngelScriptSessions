// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScriptSessionSubsystem.h"
#include "SessionMixinFunctionLibrary.generated.h"

UCLASS(Meta = (ScriptMixin = "FScriptSessionResult"))
class ANGELSCRIPTSESSIONS_API UFScriptSessionResultMixinLibrary : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(ScriptCallable)
	static bool IsValid(const FScriptSessionResult& Session);

	UFUNCTION(ScriptCallable)
	static int32 GetPingInMs(const FScriptSessionResult& Session);

	UFUNCTION(ScriptCallable)
	static FString GetServerName(const FScriptSessionResult& Session);

	UFUNCTION(ScriptCallable)
	static int32 GetCurrentPlayers(const FScriptSessionResult& Session);

	UFUNCTION(ScriptCallable)
	static int32 GetMaxPlayers(const FScriptSessionResult& Session);
};