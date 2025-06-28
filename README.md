# AngelScript Sessions

## Example Project
https://github.com/vahabahmadvand/AngelScriptSessionExample

## How to create a session
1.  Get ```UScriptSessionSubsystem``` subsystem, and bind events
```cpp
SessionSubsystem = UScriptSessionSubsystem::Get();

if (SessionSubsystem != nullptr)
{
    SessionSubsystem.OnCreateSessionCompleteEvent.AddUFunction(this, n"OnCreateSession");
    SessionSubsystem.OnFindSessionsCompleteEvent.AddUFunction(this, n"OnFindSession");
}
```

2. Having two buttons for hosting and joining
3. On Host button click, call ```CreateSession``` function.
```cpp
if (System::IsValid(SessionSubsystem))
{
    SessionSubsystem.CreateSession(NumPublicConnections, false);
}
```
4. In the ```OnCreateSession``` function, call ```ServerTravel``` to load the map and listen for the other client to join.

```cpp
UFUNCTION()
private void OnCreateSession(bool bSuccessful)
{
    FString MapName = "ThirdPersonMap?listen";

    if (bSuccessful)
    {
        GetWorld().ServerTravel(MapName, true, false);
    }
    else
    {
        Log("Failed to create session!");
    }
}
```


## How to find a session and join

1. On the Join button click, call ```FindSessions```
```cpp
if (System::IsValid(SessionSubsystem))
{
    SessionSubsystem.FindSessions(100, false);
}
```

2. In the  ```OnFindSession``` function, iterate through ```SessionResults``` sessions, then join the active session. 
    -  p.s. You can implement a listbox that includes all the sessions for the user to choose from. 

```cpp
UFUNCTION()
private void OnFindSession(const TArray<FScriptSessionResult>&in SessionResults, bool bWasSuccessful)
{
    if (System::IsValid(SessionSubsystem))
    {
        for (auto Result : SessionResults)
        {
            SessionSubsystem.JoinGameSession(Result);
            return;
        }
    }

    if (!bWasSuccessful || SessionResults.Num() == 0)
    {
        Log("Failed to find session!");
    }
}
```
