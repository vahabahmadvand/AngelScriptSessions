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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScriptSessionDelegate, bool, bSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScriptFindSessionsComplete, const TArray<FScriptSessionResult>&, SessionResults, bool, bSuccessful);


UCLASS()
class ANGELSCRIPTSESSIONS_API UScriptSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UScriptSessionSubsystem();


	UFUNCTION(ScriptCallable)
	void CreateSession(int32 NumPublicConnections, bool IsLANMatch);

	UFUNCTION(ScriptCallable)
	void UpdateSession();

	UFUNCTION(ScriptCallable)
	void EndSession();

	UFUNCTION(ScriptCallable)
	void DestroySession();

	UFUNCTION(ScriptCallable)
	void FindSessions(int32 MaxSearchResults, bool IsLANQuery);

	UFUNCTION(ScriptCallable)
	void JoinGameSession(const FScriptSessionResult& SessionResult);


	UPROPERTY(BlueprintReadOnly)
	FOnScriptSessionDelegate OnCreateSessionCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FOnScriptSessionDelegate OnUpdateSessionCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FOnScriptSessionDelegate OnEndSessionCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FOnScriptSessionDelegate OnDestroySessionCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FOnScriptFindSessionsComplete OnFindSessionsCompleteEvent;

	UPROPERTY(BlueprintReadOnly)
	FOnScriptSessionDelegate OnJoinSessionCompleteEvent;


protected:
	void OnCreateSessionCompleted(FName SessionName, bool Successful);
	void OnUpdateSessionCompleted(FName SessionName, bool Successful);
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
