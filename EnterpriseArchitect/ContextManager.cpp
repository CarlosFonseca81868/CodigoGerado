#include "ContextManager.h"
using namespace std;

void split( const String& theString, const String& theDelimiter, std::vector<String>& theStringVector)
{
    size_t  start = 0, end = 0;
    while ( end != string::npos)
    {
        end = theString.find( theDelimiter, start);
        theStringVector.push_back( theString.substr( start, (end == string::npos) ? string::npos : end - start));
        start = (( end > (string::npos - theDelimiter.size()) ) ?  string::npos  :  end + theDelimiter.size());
    }
}

//format: Event.Signal(argument1,argument2,argument3)
void GlobalFuncs::ParseEventString( String in, String& evtStr, String& signalStr, std::vector<String>& arguments)
{
	size_t pos = in.find(".");
	if(pos != String::npos) {
		evtStr = in.substr(0, pos);
		String signalWithArguments = in.substr(pos + 1);
		//format: Signal(argument1,argument2,argument3)
		size_t pos2 = signalWithArguments.find("(");
		if(pos2 != String::npos) {
			signalStr = signalWithArguments.substr(0, pos2);
			String strArguments = signalWithArguments.substr(pos2 + 1, signalWithArguments.length() - signalStr.length() - 2);
			split(strArguments, ",", arguments);
		} 
	} else {
		evtStr = in;
	}
}

void GlobalFuncs::trace(String str)
{
	cout << str;
}

StateInitialData::StateInitialData(int state_, int parent_state_, int region_count_, bool isSubmachineState_, String state_name_, String state_guid_, String instanceName_)
{
	state_enum = state_;
	parent_state_enum = parent_state_;
	region_count = region_count_;
	isSubmachineState = isSubmachineState_;
	state_name = state_name_;
	state_guid = state_guid_;
	
	instanceName = instanceName_;
}

StateData::StateData( StateMachineImpl* p, StateInitialData* pInitialData)
{
	m_pParent=p;
	state_enum = pInitialData->state_enum;
	region_count = pInitialData->region_count;
	isSubmachineState = pInitialData->isSubmachineState;
	active_count = 0;	
	parent_state = NULL;
	submachine_state = NULL;
	
	state_name = pInitialData->state_name;
	state_guid = pInitialData->state_guid;
	
	//For TimingLog
	instanceName = pInitialData->instanceName;
		
	for(int i = 0; i < 1024; i++)
		historyArray[i] = 0;
}

void StateData::IncrementActiveCount()
{
	active_count++;
	NotifyStateChange();
	if(active_count == 1)
	{
		m_pParent->GetManager()->TimingLog(instanceName, state_guid, "Activate");
	}
}

void StateData::DecrementActiveCount()
{
	active_count--;
	NotifyStateChange();
	if(active_count == 0)
	{
		m_pParent->GetManager()->TimingLog(instanceName, state_guid, "DeActivate");
	}
}

bool StateData::IsActiveState()
{
	if(active_count == 1)
		return true;
	else
		return false;
}

void StateData::NotifyStateChange()
{
	m_pParent->GetManager()->OnStateChange( this );
}

TransitionData::TransitionData()
{
	active = false;
	submachine_state = NULL;
}

void TransitionData::SetTransition(int transitionEnum_, StateData* submachineState_, String transition_name_, String guid_, String instanceName_)
{
	transition_enum = transitionEnum_;
	submachine_state = submachineState_;
	active = false;
	transition_name = transition_name_;
	transition_guid = guid_;
	instanceName = instanceName_;
}

void TransitionData::SetActive(StateMachineImpl* p)
{
	active = true;
	p->GetManager()->TimingLog(instanceName, transition_guid, "Transition");
	p->GetManager()->OnTransition(this);
}

InternalEventData::InternalEventData(Event* event_, StateData* state_)
{
	event = event_;
	AddEventReference(event);
	state = state_;
}

InternalEventData::~InternalEventData()
{
	ReleaseEvent(event);
}

StateMachineImpl::StateMachineImpl(StateMachineContext* pInstance, ContextManager* pManager)
{
	m_pInstance = pInstance;
	m_pManager = pManager;
}

StateMachineImpl::~StateMachineImpl()
{
	for (list<Event*>::iterator it = eventPool.begin(); it != eventPool.end(); it++)
	{
		Event* e = (*it);
		ReleaseEvent(e);
		eventPool.erase(it);
	}
		
	for (list<StateData*>::iterator it = lstStateData.begin(); it != lstStateData.end(); )
	{
		StateData* state = (*it);
		if(state)
		{
			bool bReleasedSomething = ReleaseSubmachineState(state);
			if(bReleasedSomething)
				it = lstStateData.begin();
			else
				it++;
		}		
	}
	
	//now the StateData* inside lstStateData don't have any submachine
	for (list<StateData*>::iterator it = lstStateData.begin(); it != lstStateData.end(); )
	{
		StateData* state = (*it);
		if(state)
			delete state;
		it = lstStateData.erase(it);
	}	
}

String StateMachineImpl::GetInstanceName()
{
	if (m_pInstance)
		return m_pInstance->GetInstanceName();
	
	return "";
}

String StateMachineImpl::GetTypeName()
{
	if (m_pInstance)
		return m_pInstance->GetTypeName();
	
	return "";
}

bool StateMachineImpl::IsTerminated()
{
	return bTerminate;
}

std::list<StateData*>* StateMachineImpl::GetStateData()
{
	return &lstStateData;	
}

ContextManager* StateMachineImpl::GetManager()
{
	return m_pManager;
}

bool StateMachineImpl::StateProc(int state, StateData* submachineState, StateBehaviorEnum behavior, Signal* signal, EntryTypeEnum enumEntryType, int entryArray[], int nArrayCount) 
{
	if (m_pInstance)
		return m_pInstance->StateProc(state, submachineState, behavior, signal, enumEntryType, entryArray, nArrayCount);
	return false;
}

void StateMachineImpl::runStateMachines()
{
	if (m_pInstance)
		m_pInstance->runStateMachines();
}

void StateMachineImpl::runStateMachine(String statemachine)
{
	if (m_pInstance)
		m_pInstance->runStateMachine(statemachine);
}

void StateMachineImpl::initializeStateMachine()
{
	bTerminate = false;
}

StateData* StateMachineImpl::GetStateObject(StateData* submachineState, int stateEnum)
{
	if(stateEnum == 0)
		return NULL;
	for (list<StateData*>::iterator it = lstStateData.begin(); it != lstStateData.end(); it++)
	{
		StateData* state = (*it);
		if(state && state->submachine_state == submachineState && state->state_enum == stateEnum)
		{
			return state;
		}		
	}
	return NULL;
}

void StateMachineImpl::CreateStateObjects(StateInitialData initialDataArray[], int nArrayCount, StateData* submachineState)
{
	for(int i = 0; i < nArrayCount; i++)
	{
		StateInitialData initialData = initialDataArray[i];		
		StateData* parentState = GetStateObject(submachineState, initialData.parent_state_enum);
		if(!parentState)
		{
			parentState = submachineState;
		}
		StateData* state = GetStateObject(submachineState, initialData.state_enum);
		if(!state)
		{
			state = new StateData(this, &initialData);
			lstStateData.push_back(state);
		}
		state->parent_state = parentState;
		state->submachine_state = submachineState;
	}
}

String StateMachineImpl::GetEventFullString(Event* event)
{
	if(!event)
	{
		return "";
	}
	String eventStr = "";
	
	std::map<EventEnum, String>::iterator itEventEnumToString = StringTable::stringTable.mapEventEnumToString.find(event->eventEnum);
	if(itEventEnumToString != StringTable::stringTable.mapEventEnumToString.end())
	{
		eventStr = itEventEnumToString->second;
		if(event->signal) {
			std::map<SignalEnum, String>::iterator itSignalEnumToString = StringTable::stringTable.mapSignalEnumToString.find(event->signal->signalEnum);
			if(itSignalEnumToString != StringTable::stringTable.mapSignalEnumToString.end())
			{
				eventStr += "." + itSignalEnumToString->second;
			}
	
			if(event->signal->parameters.size() > 0)
			{
				String signalValues = "(";
				for(std::vector<String>::iterator itParameter = event->signal->parameters.begin(); itParameter != event->signal->parameters.end(); ++itParameter)
				{
					String signalAttributeName = *itParameter;
					String signalAttributeValue = "undefined";
					
					std::map<String, String>::iterator itParameterValue = event->signal->parameterValues.find(signalAttributeName);
					if(itParameterValue != event->signal->parameterValues.end())
					{
						signalAttributeValue = itParameterValue->second;
					}
					
					if(itParameter + 1 != event->signal->parameters.end())
					{
						signalValues += signalAttributeName + ":" + signalAttributeValue + ", ";
					}
					else
					{
						signalValues += signalAttributeName + ":" + signalAttributeValue;
					}
				}
				signalValues += ")";
				eventStr += signalValues;
			}
		}
	}
	
	return eventStr;
}

bool StateMachineImpl::ReleaseSubmachineState(StateData* submachineState)
{
	bool bReleasedSomething = false;
	for (list<StateData*>::iterator it = lstStateData.begin(); it != lstStateData.end(); )
	{
		StateData* state = *it;
		if (state && state->submachine_state == submachineState)
		{
			it = lstStateData.erase(it);
			bReleasedSomething = true;
			ReleaseSubmachineState(state);
			delete state;
		}
		else
			++it;
	}
	return bReleasedSomething;
}

int StateMachineImpl::GetCurrentStates(list<StateData*>& activeStates) {
	for (list<StateData*>::iterator it = lstStateData.begin(); it != lstStateData.end(); it++)
	{
		StateData* state = (*it);
		if(state && state->IsActiveState())
		{
			activeStates.push_back(state);
		}
	}
	return (int)activeStates.size();
}

bool StateMachineImpl::recallOneInternalEvent()
{
	bool bDispatchedInternalEvent = false;
	if(lstDeferredInternalEvents.size() > 0)
	{
		InternalEventData* eventData = lstDeferredInternalEvents.front();
		lstDeferredInternalEvents.pop_front();
		if(eventData)
		{
			GlobalFuncs::trace("[" + GetInstanceName() + ":" + GetTypeName() + "] Completion: " + eventData->state->state_name);
		
			if(dispatch(eventData->event, eventData->state))
				bDispatchedInternalEvent = true;
			
			delete eventData;
		}
	}
	return bDispatchedInternalEvent;
}

void StateMachineImpl::deferInternalEvent(EventEnum eventEnum, Signal* signal, StateData* state)
{
	Event* event = new Event(eventEnum, signal);
	lstDeferredInternalEvents.push_back(new InternalEventData(event, state));
}

void StateMachineImpl::removeInternalEvent(StateData* state)
{
	for (list<InternalEventData*>::iterator itr = lstDeferredInternalEvents.begin(); itr != lstDeferredInternalEvents.end(); )
	{
		InternalEventData* pInternalEventData = *itr;
		if (pInternalEventData && pInternalEventData->state == state)
		{
			itr = lstDeferredInternalEvents.erase(itr);
			delete pInternalEventData;
		}
		else
			++itr;
	}
}

void StateMachineImpl::DumpActiveCnt()
{
	GlobalFuncs::trace("state/initial active count for [" + GetInstanceName() + ":" + GetTypeName() + "]:");
	for (list<StateData*>::iterator it = lstStateData.begin(); it != lstStateData.end(); it++)
	{
		StateData* state = (*it);
		if(state && state->state_name.find("VIRTUAL_SUBMACHINESTATE") == String::npos)
		{
			StringStream ss;
			if(state->submachine_state && state->submachine_state->state_name.find("VIRTUAL_SUBMACHINESTATE") == String::npos)
			{
				StringStream ss;
				ss << "    " << state->active_count << ", " << state->state_name << ", called by:" << state->submachine_state->state_name << endl;
			}
			else
			{
				ss << "    " << state->active_count << ", " << state->state_name << endl;
			}
			GlobalFuncs::trace(ss.str());
		}	
	}
	
	DumpEvents();
}

void StateMachineImpl::DumpEvents() {
	if(eventPool.size() == 0)
		return;
	
	GlobalFuncs::trace("Event Pool: [");
	for (list<Event*>::iterator it = eventPool.begin(); it != eventPool.end(); it++)
	{
		String eventFullString = GetEventFullString(*it);
		if(eventFullString != "")
		{
			GlobalFuncs::trace(eventFullString + ",");
		}
	}	
	GlobalFuncs::trace("]");
}

void StateMachineImpl::EventOccurance(EventEnum eventEnum, Signal* signal)
{
	Event* event = new Event(eventEnum, signal);
	AddEventReference(event);
    eventPool.push_back(event);
	
	String eventFullString = GetEventFullString(event);
	if(eventFullString != "")
	{
		GlobalFuncs::trace("[" + GetInstanceName() + ":" + GetTypeName() + "] Event Queued: " + eventFullString);
	}
}

	
void StateMachineImpl::recall()
{
	for (list<Event*>::iterator it = eventPool.begin(); it != eventPool.end();)
	{
		Event* e = (*it);
		if(!defer(e))
		{
			String eventFullString = GetEventFullString(e);
			if(eventFullString != "")
			{
				GlobalFuncs::trace("[" + GetInstanceName() + ":" + GetTypeName() + "] Event Dispatched: " + eventFullString);
			}
	
			//it is not deferred, remove from eventPool and dispatch it; if not consumed, iterate to the next event in the queue
			it = eventPool.erase(it);
			bool bDispatched = dispatch(e);
			if(bDispatched){
				break;
			}
		}
		else
			it++;
	}
}

bool StateMachineImpl::defer(Event* event)
{
    if (event->eventEnum == COMPLETION)
        return false;
	list<StateData*> activeStates;
	int nCurrentStateCount = GetCurrentStates(activeStates);
	
	bool bDeferred = false;
	for (list<StateData*>::iterator it = activeStates.begin(); it != activeStates.end(); it++)
	{
		StateData* pActiveState = (*it);
		bool bDeferredToState = defer(event, pActiveState);
		if(bDeferredToState)
		{
			bDeferred = true;
			break;
		}
	}
	return bDeferred;
}

bool StateMachineImpl::defer(Event* event, StateData* toState)
{
	if (m_pInstance)
		return m_pInstance->defer(event, toState);
	return false;
}

bool StateMachineImpl::dispatch(String eventStr)
{
	String evtStr;
	String signalStr;
	std::vector<String> arguments;
	
	GlobalFuncs::ParseEventString(eventStr, evtStr, signalStr, arguments);
	Signal* signal = GetSignalInstance(signalStr, arguments);
	bool returnVal = dispatch( StringTable::stringTable.mapStringToEventEnum[evtStr], signal);
	
	return returnVal;
}

bool StateMachineImpl::dispatch(EventEnum eventEnum, Signal* signal) 
{
	Event* event = new Event(eventEnum, signal);
	AddEventReference(event);
	return dispatch(event);
}

bool StateMachineImpl::dispatch(Event* event) 
{
	bool bDispatched = false;
	
	list<StateData*> activeStates;
	int nCurrentStateCount = GetCurrentStates(activeStates);
	
	for (list<StateData*>::iterator it = activeStates.begin(); it != activeStates.end(); it++)
	{
		StateData* pActiveState = (*it);
		bool bDispatchedToState = dispatch(event, pActiveState, false);
		if(bDispatchedToState)
			bDispatched = true;
	}
	
	ReleaseEvent(event);
	return bDispatched;
}

bool StateMachineImpl::dispatch(Event* event, StateData* toState)
{
	return dispatch(event, toState, false);
}

bool StateMachineImpl::dispatch(Event* event, StateData* toState, bool bCheckOnly) 
{
	if(bCheckOnly == false)
	{
		GetManager()->TimingEventLog(GetEventFullString(event), toState->state_guid);
	}
		
	if (m_pInstance)
		return m_pInstance->dispatch(event, toState, bCheckOnly);
	
	return false;
}

void StateMachineImpl::DoDeepHistory(StateData* submachineState, int history)
{
	StateProc(history, submachineState, ENTRY, 0, HistoryEntry);
	StateData* historyObject = GetStateObject(submachineState, history);
	if(!historyObject)
		return;	//should not happen
	
	for(int i = 0; i < historyObject->region_count; i++)
	{
		int nextHistory = historyObject->historyArray[i];
		if(nextHistory != 0)
		{
			historyObject->IncrementActiveCount();
			if(historyObject->isSubmachineState)
				DoDeepHistory(historyObject, nextHistory);
			else
				DoDeepHistory(submachineState, nextHistory);
		}
	}
}

ContextManager::~ContextManager()
{
	for (list<StateMachineImpl*>::iterator itr = lstContext.begin(); itr != lstContext.end(); itr++)
	{
		StateMachineImpl* pContext = *itr;
		if (pContext)
		{
			// Delete the object through delete its container instance
			if (pContext->m_pInstance)
			{
				delete pContext->m_pInstance;
			}
		}
	}
	lstContext.clear();
}

void ContextManager::TimingEventLog(String eventName, String stateGuid)
{
	DWORD timeNow = GetTickCount();
	long lTimeElapsedInMS = (long)(timeNow - simulationStartTime);
	
	StringStream ss;
	ss << lTimeElapsedInMS << "," << eventName << "," << stateGuid << endl;
	
	lstTimingEventLog.push_back(ss.str());
}

void ContextManager::TimingLog(String instanceName, String stateGuid, String action)
{
	DWORD timeNow = GetTickCount();
	long lTimeElapsedInMS = (long)(timeNow - simulationStartTime);
	
	StringStream ss;
	ss << lTimeElapsedInMS << "," << instanceName << "," << stateGuid << "," << action << endl;
	lstTimingLog.push_back(ss.str());
}

void ContextManager::DumpTimingLog()
{
	GlobalFuncs::trace("TimingEventLog Begin\n");
	for(list<String>::iterator itr = lstTimingEventLog.begin(); itr != lstTimingEventLog.end(); itr++)
	{
		String str = *itr;
		GlobalFuncs::trace("\t" + str + "\n");
	}	
	GlobalFuncs::trace("TimingEventLog End\n");
	
	GlobalFuncs::trace("TimingLog Begin\n");
	for(list<String>::iterator itr = lstTimingLog.begin(); itr != lstTimingLog.end(); itr++)
	{
		String str = *itr;
		GlobalFuncs::trace("\t" + str + "\n");
	}
	GlobalFuncs::trace("TimingLog End\n");
}

	
void ContextManager::initialize()
{
	for(list<StateMachineImpl*>::iterator itr = lstContext.begin(); itr != lstContext.end(); itr++)
	{
		StateMachineImpl* pContext = *itr;
		if(pContext)
		{
			pContext->initializeStateMachine();
		}
	}
}

void ContextManager::RunAllStateMachines()
{
	for(list<StateMachineImpl*>::iterator itr = lstContext.begin(); itr != lstContext.end(); itr++)
	{
		StateMachineImpl* pContext = *itr;
		if(pContext)
		{
			pContext->runStateMachines();
		}
	}
}

void ContextManager::BroadCastEvent(String eventStr)
{
	String evtStr;
	String signalStr;
	std::vector<String> arguments;
	GlobalFuncs::ParseEventString(eventStr, evtStr, signalStr, arguments);
	Signal* signal = GetSignalInstance(signalStr, arguments);
	BroadCastEvent( StringTable::stringTable.mapStringToEventEnum[evtStr], signal);
}

void ContextManager::BroadCastEvent(EventEnum eventEnum_, Signal* signal)
{
	for(list<StateMachineImpl*>::iterator itr = lstContext.begin(); itr != lstContext.end(); itr++)
	{
		StateMachineImpl* pContext = *itr;
		if(pContext)
		{
			pContext->EventOccurance(eventEnum_, signal);
		}
	}
}

void ContextManager::SendEvent(String eventStr, String contextStr)
{
	StateMachineImpl* context = NULL;
	for(list<StateMachineImpl*>::iterator itr = lstContext.begin(); itr != lstContext.end(); itr++)
	{
		StateMachineImpl* pContext = *itr;
		if(pContext && contextStr.compare(pContext->GetInstanceName()) == 0)
		{
			context = pContext;
			break;
		}
	}
	if(context)
	{
		SendEvent(eventStr, context);
	}
}

void ContextManager::SendEvent(String eventStr, StateMachineImpl* target)
{
	if (target)
    {
		String evtStr;
		String signalStr;
		std::vector<String> arguments;
		
		GlobalFuncs::ParseEventString(eventStr, evtStr, signalStr, arguments);
		Signal* signal = GetSignalInstance(signalStr, arguments);
        if (StringTable::stringTable.mapStringToEventEnum[evtStr])
            SendEvent(StringTable::stringTable.mapStringToEventEnum[evtStr], signal, target);
    }
}

void ContextManager::SendEvent(EventEnum eventEnum_, Signal* signal, StateMachineImpl* target)
{
	if(target)
		target->EventOccurance(eventEnum_, signal);
}

bool ContextManager::EvaluateCommandString(String commandStr)
{
	if(commandStr != "")
	{
		GlobalFuncs::trace("Command: " + commandStr);
	}
			
	String command = "";
	String instance = "";
	String statemachine = "";
	String eventString = "";
	if(commandStr.find("run ") != String::npos) {
		command = "run";
		String argument = commandStr.substr(4);
		size_t pos = argument.find(".");
		if(pos != String::npos) {
			instance = argument.substr(0, pos);
			statemachine = argument.substr(pos + 1);
		} else if(argument.compare("all") == 0) {
			instance = "all";
			statemachine = "all";
		} else if(!argument.empty())
		{
			instance = argument;
			statemachine = "all";
		}
	} else if(commandStr.compare("run") == 0) {
		command = "run";
		instance = "all";
		statemachine = "all";		
	} else if(commandStr.find("broadcast ") != String::npos) {
		command = "broadcast";
		instance = "all";
		eventString = commandStr.substr(10);
		BroadCastEvent(eventString);
	} else if(commandStr.find("send ") != String::npos) {
		command = "send";
		String argument = commandStr.substr(5);
		size_t pos = argument.find(" to ");
		if(pos != String::npos) {
			eventString = argument.substr(0, pos);
			instance = argument.substr(pos + 4);
		}
		else
		{
			eventString = argument;
			instance = "all";
		}
	} else if(commandStr.find("dump ") != String::npos) {
		command = "dump";
		instance = commandStr.substr(5);
	} else if(commandStr.compare("dump") == 0) {
		command = "dump";
		instance = "all";
	} else if(commandStr.compare("dumpTimingLog") == 0) {
		DumpTimingLog();
		return true;
	} else if (commandStr.compare("exit") == 0) {
		command = "exit";
		return false;
	} else if (commandStr.compare("stepall") == 0) {
		command = "stepall";
		instance = "all";
	} else {
		command = "step";
		instance = "all";
	}
	for(list<StateMachineImpl*>::iterator itr = lstContext.begin(); itr != lstContext.end(); itr++)
	{
		StateMachineImpl* pContext = *itr;
		if(pContext)
		{
			if (command.compare("broadcast") != 0)
            {
                if(instance.compare("all") == 0 || instance.compare(pContext->GetInstanceName()) == 0)
				{
					RunCommand(command, pContext, statemachine, eventString);				
					if(instance.compare(pContext->GetInstanceName()) == 0)
						break;
				}
            }
            else
            {
                pContext->recall();
            }
		}
	}
	
	//if any of the context reach a terminiate
	for(list<StateMachineImpl*>::iterator itr = lstContext.begin(); itr != lstContext.end(); )
	{
		StateMachineImpl* pContext = *itr;
		if(pContext && pContext->IsTerminated())
		{
			itr = lstContext.erase(itr);
			// Delete the object through delete its container instance.
			if (pContext->m_pInstance)
			{
				ClearInstance(pContext->GetInstanceName());
				delete pContext->m_pInstance;
			}
		}
		else
			itr++;
	}
	
	if(IsSimulationEnded())
	{
		return false;
	}
	
	return true;	
}

bool ContextManager::IsSimulationEnded()
{
	bool bIsSimulationEnded = true;
	for(list<StateMachineImpl*>::iterator itContext = lstContext.begin(); itContext != lstContext.end(); ++itContext)
	{
		StateMachineImpl* pContext = *itContext;
		if(pContext)
		{
			for (list<StateData*>::iterator itStates = pContext->lstStateData.begin(); itStates != pContext->lstStateData.end(); itStates++)
			{
				StateData* state = (*itStates);
				if(state && state->active_count > 0)
				{
					bIsSimulationEnded = false;
					break;
				}
			}
			
			if(!bIsSimulationEnded){
				break;
			}
		}
	}
	return bIsSimulationEnded;
}

void ContextManager::RunCommand(String command, StateMachineImpl* context, String statemachine, String eventString)
{
	if(context == NULL)
		return;
	if(command.compare("run") == 0) {
		if(statemachine.compare("all") == 0)
			context->runStateMachines();
		else
			context->runStateMachine(statemachine);
	} else if(command.compare("send") == 0) {
		SendEvent(eventString, context);
		
	} else if(command.compare("dump") == 0) {
		context->DumpActiveCnt();
	} else if(command.compare("stepall") == 0) {
		while(true)
		{
			if(!context->recallOneInternalEvent())
				break;
		}
		//This is a wait point, get an event from the pool and dispatch it
        context->recall();
	} else if(command.compare("step") == 0) {
		if (!context->recallOneInternalEvent())
        {
            //This is a wait point, get an event from the pool and dispatch it
            context->recall();
        }
	}
}

void ContextManager::ClearInstance(String instanceStr)
{
}

void ContextManager::Run()
{
}

void ContextManager::OnStateChange( StateData* pState)
{
}

void ContextManager::OnTransition( TransitionData* pTransition)
{
}
