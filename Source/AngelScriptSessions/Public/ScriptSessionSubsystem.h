// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "ScriptSessionSubsystem.generated.h"

using namespace EOnJoinSessionCompleteResult;

USTRUCT(BlueprintType)
struct FScriptSessionResult
{
	GENERATED_USTRUCT_BODY()

	FOnlineSessionSearchResult OnlineResult;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScriptOnCreateSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScriptOnUpdateSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScriptOnStartSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScriptOnEndSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScriptOnDestroySessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScriptOnJoinSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FScriptOnFindSessionsComplete, const TArray<FScriptSessionResult>&, SessionResults, bool, Successful);


UCLASS()
class UScriptSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UScriptSessionSubsystem();

	UFUNCTION(ScriptCallable)
	void CreateSession(int32 NumPublicConnections, bool IsLANMatch);

	UFUNCTION(ScriptCallable)
	void UpdateSession();

	UFUNCTION(ScriptCallable)
	void StartSession();

	UFUNCTION(ScriptCallable)
	void EndSession();

	UFUNCTION(ScriptCallable)
	void DestroySession();

	UFUNCTION(ScriptCallable)
	void FindSessions(int32 MaxSearchResults, bool IsLANQuery);

	UFUNCTION(ScriptCallable)
	void JoinGameSession(const FScriptSessionResult& SessionResult);
	
	UPROPERTY(BlueprintReadOnly)
	FScriptOnCreateSessionComplete OnCreateSessionCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FScriptOnUpdateSessionComplete OnUpdateSessionCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FScriptOnStartSessionComplete OnStartSessionCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FScriptOnEndSessionComplete OnEndSessionCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FScriptOnDestroySessionComplete OnDestroySessionCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FScriptOnFindSessionsComplete OnFindSessionsCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FScriptOnJoinSessionComplete OnJoinSessionCompleteEvent;


protected:
	void OnCreateSessionCompleted(FName SessionName, bool Successful);
	void OnUpdateSessionCompleted(FName SessionName, bool Successful);
	void OnStartSessionCompleted(FName SessionName, bool Successful);
	void OnEndSessionCompleted(FName SessionName, bool Successful);
	void OnDestroySessionCompleted(FName SessionName, bool Successful);
	void OnFindSessionsCompleted(bool Successful);
	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	bool TryTravelToCurrentSession();

private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	FOnUpdateSessionCompleteDelegate UpdateSessionCompleteDelegate;
  	FDelegateHandle UpdateSessionCompleteDelegateHandle;

	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	FOnEndSessionCompleteDelegate EndSessionCompleteDelegate;
	FDelegateHandle EndSessionCompleteDelegateHandle;

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;

	
};
