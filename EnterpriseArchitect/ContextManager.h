#pragma once
#include <windows.h>			//Timing Logging requested GetTickCount()
#include <iostream>
#include <list>
#include <map>
#include <deque>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
#include <time.h>
#include "EventProxy.h"
// DEFINE BASIC CHARACTER TYPE
#ifdef UNICODE
#define TCHAR wchar_t 
#define _T(x) L##x
#else
#define TCHAR char 	
#define _T(x) x
#endif
// DEFINE BASIC STRING TYPE
typedef std::basic_string<TCHAR>  String;
typedef std::basic_stringstream<TCHAR>  StringStream;
#define SHARED_MEMORY_STRING_LENGTH 1024
#define ASSERT assert
#define MAX_STATES 1024


//forward declaration
class ContextManager;	
class StateMachineContext;
class StateMachineImpl;


enum StateBehaviorEnum 
{
	ENTRY,
	DO,
	EXIT,
};

enum EntryTypeEnum
{
	DefaultEntry,
	ExplicitEntry,
	HistoryEntry,
	EntryPointEntry,
};

	
class StateInitialData {
public:
	StateInitialData(int state_, int parent_state_, int region_count_, bool isSubmachineState_, String state_name_, String state_guid_, String instanceName_);
	int state_enum;
	int parent_state_enum;
	int region_count;				//submachineState's region count == submachine's region count
	bool isSubmachineState;
	String state_name;
	String state_guid;
	String instanceName;		//For Timing Logging
};

class StateData
{
public:
	StateMachineImpl* m_pParent;
	StateData(StateMachineImpl* p, StateInitialData* pInitialData);
	void IncrementActiveCount();
	void DecrementActiveCount();
	bool IsActiveState();
	void NotifyStateChange();
	
	int active_count;			//when entry, ++; when exit --;	besides, for orthogonal state: when region get activated, ++; when region deActivated, --
	int region_count;				//submachineState's region count == submachine's region count
	bool isSubmachineState;
	String state_name;
	String state_guid;
	String instanceName;	//For Timing Logging
	
	int state_enum;
	StateData* parent_state;
	StateData* submachine_state;
	int historyArray[1024];	//array entry represent for each region, the value is the Last Active State's Enum; in order to support history mechanism on submachine state, can not use StateData* as type
};

class TransitionData
{
public:
	TransitionData();
	void SetTransition(int transitionEnum_, StateData* submachineState_, String transition_name_, String guid_, String instanceName_);
	void SetActive(StateMachineImpl*);
	int transition_enum;
	StateData* submachine_state;
	bool active;
	String transition_name;
	String transition_guid;
	String instanceName;	//For Timing Logging
};

class InternalEventData {
public:
	InternalEventData(Event* event_, StateData* state_);
	virtual ~InternalEventData();
	Event* event;
	StateData* state;
};

template<typename T>
String to_str(const T& value){
  StringStream ss;
  ss << value;
  return ss.str();
};

class GlobalFuncs {
public:
	
	static void ParseEventString( String in,    String& evtStr, String& signalStr, std::vector<String>& arguments);
	static void trace(String str);
};

class StateMachineContext {
public:
	virtual void runStateMachines() = 0;
	virtual void runStateMachine(String statemachine) = 0;
	virtual bool dispatch(Event* event, StateData* toState, bool bCheckOnly) = 0;
	virtual bool StateProc(int state, StateData* submachineState, StateBehaviorEnum behavior, Signal* signal, EntryTypeEnum enumEntryType, int entryArray[], int nArrayCount) = 0;
	virtual bool defer(Event* event, StateData* toState) = 0;
	virtual String GetInstanceName()=0;
	virtual String GetTypeName()=0;
};

class StateMachineImpl
{
public:
	StateMachineImpl(StateMachineContext* pInstance, ContextManager* pManager);
	virtual ~StateMachineImpl();
	
	// Owner StateMachineContext instance
	StateMachineContext* m_pInstance;
	
    ContextManager* m_pManager;
	TransitionData currentTransition;
	std::list<StateData*> lstStateData;
	std::list<InternalEventData*> lstDeferredInternalEvents;		//in order to simulate concurrent in a liner way
	std::list<Event*> eventPool;
	bool bTerminate;
	
	String GetInstanceName();
	String GetTypeName();
	
	bool IsTerminated();
	
	std::list<StateData*>* GetStateData();
	ContextManager* GetManager();
	
	bool StateProc(int state, StateData* submachineState, StateBehaviorEnum behavior, Signal* signal, EntryTypeEnum enumEntryType = DefaultEntry, int entryArray[] = NULL, int nArrayCount = 0);
	
	void runStateMachines();
	void runStateMachine(String statemachine);
	
	void initializeStateMachine();
	
	StateData* GetStateObject(StateData* submachineState, int stateEnum);
	void CreateStateObjects(StateInitialData initialDataArray[], int nArrayCount, StateData* submachineState);
	
	String GetEventFullString(Event* event);
	
	bool ReleaseSubmachineState(StateData* submachineState);
	int GetCurrentStates(std::list<StateData*>& activeStates);
	bool recallOneInternalEvent();
	void deferInternalEvent(EventEnum eventEnum, Signal* signal, StateData* state);
	void removeInternalEvent(StateData* state);
	void DumpActiveCnt();
	void DumpEvents();
	
	void EventOccurance(EventEnum eventEnum, Signal* signal);
	void recall();
	bool defer(Event* event);
	bool defer(Event* event, StateData* toState);
	bool dispatch(String eventStr);
	bool dispatch(EventEnum eventEnum, Signal* signal);
	bool dispatch(Event* event);
	bool dispatch(Event* event, StateData* toState);
	bool dispatch(Event* event, StateData* toState, bool bCheckOnly);
	void DoDeepHistory(StateData* submachineState, int history);	
};

class ContextManager
{
public:
	ContextManager(){};
	virtual ~ContextManager();
	std::list<StateMachineImpl*> lstContext;
	void initialize();
	void RunAllStateMachines();
	void BroadCastEvent(String eventStr);
	void BroadCastEvent(EventEnum eventEnum_, Signal* signal);
	void SendEvent(String eventStr, String contextStr);

	void SendEvent(String eventStr, StateMachineImpl* target);
	void SendEvent(EventEnum eventEnum_, Signal* signal, StateMachineImpl* target);
	bool EvaluateCommandString(String commandStr);													//return true if continue waiting for next command; return false if break
	void RunCommand(String command, StateMachineImpl* context, String statemachine, String eventString);	//return true if continue waiting for next command; return false if break
	bool IsSimulationEnded();
	virtual void ClearInstance(String instanceStr);
	virtual void Run();
	virtual void OnStateChange( StateData *);		//SimulationManager will overwrite
	virtual void OnTransition( TransitionData *);	//SimulationManager will overwrite
	
	//for Timing Logging
	DWORD simulationStartTime;			//Windows Only
	std::list<String> lstTimingEventLog;
	std::list<String> lstTimingLog;
	void TimingEventLog(String eventName, String stateGuid);
	void TimingLog(String instanceName, String stateGuid, String action);
	void DumpTimingLog();
};
