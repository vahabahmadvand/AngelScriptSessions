// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionMixinFunctionLibrary.h"

int32 UFScriptSessionResultMixinLibrary::GetPingInMs(const FScriptSessionResult& Session)
{
	return Session.OnlineResult.PingInMs;
}

FString UFScriptSessionResultMixinLibrary::GetServerName(const FScriptSessionResult& Session)
{
	return Session.OnlineResult.Session.OwningUserName;
}

int32 UFScriptSessionResultMixinLibrary::GetCurrentPlayers(const FScriptSessionResult& Session)
{
	return Session.OnlineResult.Session.SessionSettings.NumPublicConnections - Session.OnlineResult.Session.NumOpenPublicConnections;;
}

int32 UFScriptSessionResultMixinLibrary::GetMaxPlayers(const FScriptSessionResult& Session)
{
	return Session.OnlineResult.Session.SessionSettings.NumPublicConnections;
}

bool UFScriptSessionResultMixinLibrary::IsValid(const FScriptSessionResult& Session)
{
	return Session.OnlineResult.IsSessionInfoValid() && Session.OnlineResult.Session.NumOpenPublicConnections > 0;
}
