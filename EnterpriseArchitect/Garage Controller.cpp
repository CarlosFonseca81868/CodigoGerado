///////////////////////////////////////////////////////////
//  Garage Controller.cpp
//  Implementation of the Class Garage Controller
//  Created on:      15-jun-2022 14:58:38
//  Original author: Carlos
///////////////////////////////////////////////////////////

#include "Garage Controller.h"

using namespace std;



void Garage Controller::abrir(){

}


void Garage Controller::BotaoPremido(){

}


void Garage Controller::fechar(){

}


void Garage Controller::fim_stop(){

}


void Garage Controller::stop(){

}


void Garage Controller::stop_fecho(){

}


/* Begin - EA generated code for StateMachine */








GarageController::GarageController()
{
	m_StateMachineImpl = NULL;
}

GarageController::GarageController(ContextManager* pManager, String sInstanceName)
{
	//Initialize Region Variables
	m_garagestatemachine = NOSTATE;
    m_sInstanceName = sInstanceName;
    m_sType = "Garage Controller";
	m_StateMachineImpl = new StateMachineImpl(this, pManager);
}

GarageController::~GarageController()
{
	if (m_StateMachineImpl)
	{
		delete m_StateMachineImpl;
	}
}

bool GarageController::defer(Event* event, StateData* toState)
{
	bool bDefer = false;
		
	if(!bDefer)
	{
		if(toState->parent_state)
		{
			bDefer = defer(event, toState->parent_state);
		}
	}
	return bDefer;
}


void GarageController::TransitionProc(TransitionEnum transition, Signal* signal, StateData* submachineState) 
{
	if (!m_StateMachineImpl)
		return;
	
	switch (transition) {
		case GarageController_ENUM_ABERTA__TO__AFECHAR_5:
			m_StateMachineImpl->currentTransition.SetTransition(transition, submachineState, "GarageController_Aberta__TO__AFechar_5", "{2F094BEF-B5EB-4f71-9BF6-C0BBB8975EBC}", m_sInstanceName);
			Aberta__TO__AFechar_5(signal, submachineState); 
			break;

		case GarageController_ENUM_FECHADA__TO__AABRIR_3:
			m_StateMachineImpl->currentTransition.SetTransition(transition, submachineState, "GarageController_Fechada__TO__AAbrir_3", "{41507C82-BC14-40ae-92F5-8DA07B1E3860}", m_sInstanceName);
			Fechada__TO__AAbrir_3(signal, submachineState); 
			break;

		case GarageController_ENUM_AFECHAR__TO__AABRIR_7:
			m_StateMachineImpl->currentTransition.SetTransition(transition, submachineState, "GarageController_AFechar__TO__AAbrir_7", "{5597D75D-11E1-473f-9560-77B32FA0FDD0}", m_sInstanceName);
			AFechar__TO__AAbrir_7(signal, submachineState); 
			break;

		case GarageController_ENUM_ENTRYPOINT_5_5__TO__FECHADA_2:
			m_StateMachineImpl->currentTransition.SetTransition(transition, submachineState, "GarageController_entryPoint_5_5__TO__Fechada_2", "{5CA788E8-D936-43e3-8F47-88EDAB010646}", m_sInstanceName);
			entryPoint_5_5__TO__Fechada_2(signal, submachineState); 
			break;

		case GarageController_ENUM_AFECHAR__TO__FECHADA_6:
			m_StateMachineImpl->currentTransition.SetTransition(transition, submachineState, "GarageController_AFechar__TO__Fechada_6", "{7F07B99A-9FBC-4859-9752-EB9AC30FD3EE}", m_sInstanceName);
			AFechar__TO__Fechada_6(signal, submachineState); 
			break;

		case GarageController_ENUM_AABRIR__TO__ABERTA_4:
			m_StateMachineImpl->currentTransition.SetTransition(transition, submachineState, "GarageController_AAbrir__TO__Aberta_4", "{EEB6C0F1-841D-4d56-93AF-B9CAA1E45074}", m_sInstanceName);
			AAbrir__TO__Aberta_4(signal, submachineState); 
			break;
	}
	m_StateMachineImpl->currentTransition.SetTransition(NOTRANSITION, NULL, "NOTRANSITION", "", "");
}

void GarageController::Aberta__TO__AFechar_5_effect(Signal* signal)
{
	StringStream ss;
	ss << "[" << m_sInstanceName << ":" << m_sType << "] Transition Effect: " << "Aberta__TO__AFechar_5 " << endl;
	GlobalFuncs::trace(ss.str());
	
}

void GarageController::Aberta__TO__AFechar_5(Signal* signal, StateData* submachineState) 
{
	if (!m_StateMachineImpl)
		return;
	
	if(!m_StateMachineImpl->GetStateObject(submachineState, GarageController_ENUM_GARAGESTATEMACHINE_ABERTA)->IsActiveState())
	{
		return;
	}
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_ABERTA, submachineState, EXIT, 0);
	Aberta__TO__AFechar_5_effect(signal);
	m_StateMachineImpl->currentTransition.SetActive(m_StateMachineImpl);
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR, submachineState, ENTRY, signal, DefaultEntry);
}

void GarageController::Fechada__TO__AAbrir_3_effect(Signal* signal)
{
	StringStream ss;
	ss << "[" << m_sInstanceName << ":" << m_sType << "] Transition Effect: " << "Fechada__TO__AAbrir_3 " << endl;
	GlobalFuncs::trace(ss.str());
	
}

void GarageController::Fechada__TO__AAbrir_3(Signal* signal, StateData* submachineState) 
{
	if (!m_StateMachineImpl)
		return;
	
	if(!m_StateMachineImpl->GetStateObject(submachineState, GarageController_ENUM_GARAGESTATEMACHINE_FECHADA)->IsActiveState())
	{
		return;
	}
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_FECHADA, submachineState, EXIT, 0);
	Fechada__TO__AAbrir_3_effect(signal);
	m_StateMachineImpl->currentTransition.SetActive(m_StateMachineImpl);
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_AABRIR, submachineState, ENTRY, signal, DefaultEntry);
}

void GarageController::AFechar__TO__AAbrir_7_effect(Signal* signal)
{
	StringStream ss;
	ss << "[" << m_sInstanceName << ":" << m_sType << "] Transition Effect: " << "AFechar__TO__AAbrir_7 " << endl;
	GlobalFuncs::trace(ss.str());
	
}

void GarageController::AFechar__TO__AAbrir_7(Signal* signal, StateData* submachineState) 
{
	if (!m_StateMachineImpl)
		return;
	
	if(!m_StateMachineImpl->GetStateObject(submachineState, GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR)->IsActiveState())
	{
		return;
	}
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR, submachineState, EXIT, 0);
	AFechar__TO__AAbrir_7_effect(signal);
	m_StateMachineImpl->currentTransition.SetActive(m_StateMachineImpl);
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_AABRIR, submachineState, ENTRY, signal, DefaultEntry);
}

void GarageController::entryPoint_5_5__TO__Fechada_2_effect(Signal* signal)
{
	StringStream ss;
	ss << "[" << m_sInstanceName << ":" << m_sType << "] Transition Effect: " << "entryPoint_5_5__TO__Fechada_2 " << endl;
	GlobalFuncs::trace(ss.str());
	
}

void GarageController::entryPoint_5_5__TO__Fechada_2(Signal* signal, StateData* submachineState) 
{
	if (!m_StateMachineImpl)
		return;
	
	entryPoint_5_5__TO__Fechada_2_effect(signal);
	m_StateMachineImpl->currentTransition.SetActive(m_StateMachineImpl);
	submachineState->IncrementActiveCount();	//local transition activate the region
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_FECHADA, submachineState, ENTRY, signal, DefaultEntry);
}

void GarageController::AFechar__TO__Fechada_6_effect(Signal* signal)
{
	StringStream ss;
	ss << "[" << m_sInstanceName << ":" << m_sType << "] Transition Effect: " << "AFechar__TO__Fechada_6 " << endl;
	GlobalFuncs::trace(ss.str());
	
}

void GarageController::AFechar__TO__Fechada_6(Signal* signal, StateData* submachineState) 
{
	if (!m_StateMachineImpl)
		return;
	
	if(!m_StateMachineImpl->GetStateObject(submachineState, GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR)->IsActiveState())
	{
		return;
	}
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR, submachineState, EXIT, 0);
	AFechar__TO__Fechada_6_effect(signal);
	m_StateMachineImpl->currentTransition.SetActive(m_StateMachineImpl);
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_FECHADA, submachineState, ENTRY, signal, DefaultEntry);
}

void GarageController::AAbrir__TO__Aberta_4_effect(Signal* signal)
{
	StringStream ss;
	ss << "[" << m_sInstanceName << ":" << m_sType << "] Transition Effect: " << "AAbrir__TO__Aberta_4 " << endl;
	GlobalFuncs::trace(ss.str());
	
}

void GarageController::AAbrir__TO__Aberta_4(Signal* signal, StateData* submachineState) 
{
	if (!m_StateMachineImpl)
		return;
	
	if(!m_StateMachineImpl->GetStateObject(submachineState, GarageController_ENUM_GARAGESTATEMACHINE_AABRIR)->IsActiveState())
	{
		return;
	}
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_AABRIR, submachineState, EXIT, 0);
	AAbrir__TO__Aberta_4_effect(signal);
	m_StateMachineImpl->currentTransition.SetActive(m_StateMachineImpl);
	StateProc(GarageController_ENUM_GARAGESTATEMACHINE_ABERTA, submachineState, ENTRY, signal, DefaultEntry);
}

bool GarageController::StateProc(int state, StateData* submachineState, StateBehaviorEnum behavior, Signal* signal, EntryTypeEnum enumEntryType, int entryArray[], int nArrayCount) 
{
	EntryEnum entryEnumArray[MAX_STATES];
	for(int i = 0; i < nArrayCount; i++)
	{
		entryEnumArray[i] = (EntryEnum)entryArray[i];
	}
	
	return StateProc((StateEnum)state, submachineState, behavior, signal, enumEntryType, entryEnumArray, nArrayCount);
}
bool GarageController::StateProc(StateEnum state, StateData* submachineState, StateBehaviorEnum behavior, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount) 
{
	switch (state) {
		case GarageController_ENUM_GARAGESTATEMACHINE_AABRIR:
			return GarageStateMachine_AAbrir(behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);

		case GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR:
			return GarageStateMachine_AFechar(behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);

		case GarageController_ENUM_GARAGESTATEMACHINE_ABERTA:
			return GarageStateMachine_Aberta(behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);

		case GarageController_ENUM_GARAGESTATEMACHINE_FECHADA:
			return GarageStateMachine_Fechada(behavior, submachineState, signal, enumEntryType, entryArray, nArrayCount);
	}
	return false;
}

bool GarageController::GarageStateMachine_AAbrir(StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount)
{
	if (!m_StateMachineImpl)
		return false;
	
	StateData*  state = m_StateMachineImpl->GetStateObject(submachineState, GarageController_ENUM_GARAGESTATEMACHINE_AABRIR);
	switch (behavior) {
		case ENTRY:
			if(state->active_count > 0)
				return false;
			m_garagestatemachine = GarageController_ENUM_GARAGESTATEMACHINE_AABRIR;
			state->IncrementActiveCount();
			GarageStateMachine_AAbrir_behavior(ENTRY, signal);
			
			GarageStateMachine_AAbrir_behavior(DO, signal);
			if((enumEntryType == EntryPointEntry || enumEntryType == DefaultEntry) && state->IsActiveState())
				m_StateMachineImpl->deferInternalEvent(COMPLETION, 0, state);
			break;
		case EXIT:
			if(state->active_count == 0)
				return false;
			m_garagestatemachine = NOSTATE;
			state->DecrementActiveCount();
			GarageStateMachine_AAbrir_behavior(EXIT, signal);
			m_StateMachineImpl->removeInternalEvent(state);
			break;
	}
	
	return true;
}

bool GarageController::GarageStateMachine_AAbrir_behavior(StateBehaviorEnum behavior, Signal* signal) 
{
	switch (behavior) {
		case ENTRY:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Entry Behavior: " << "GarageStateMachine_AAbrir " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
		case DO:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Do Behavior: " << "GarageStateMachine_AAbrir " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
		case EXIT:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Exit Behavior: " << "GarageStateMachine_AAbrir " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
	}
	
	return true;
}

bool GarageController::GarageStateMachine_AFechar(StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount)
{
	if (!m_StateMachineImpl)
		return false;
	
	StateData*  state = m_StateMachineImpl->GetStateObject(submachineState, GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR);
	switch (behavior) {
		case ENTRY:
			if(state->active_count > 0)
				return false;
			m_garagestatemachine = GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR;
			state->IncrementActiveCount();
			GarageStateMachine_AFechar_behavior(ENTRY, signal);
			
			GarageStateMachine_AFechar_behavior(DO, signal);
			if((enumEntryType == EntryPointEntry || enumEntryType == DefaultEntry) && state->IsActiveState())
				m_StateMachineImpl->deferInternalEvent(COMPLETION, 0, state);
			break;
		case EXIT:
			if(state->active_count == 0)
				return false;
			m_garagestatemachine = NOSTATE;
			state->DecrementActiveCount();
			GarageStateMachine_AFechar_behavior(EXIT, signal);
			m_StateMachineImpl->removeInternalEvent(state);
			break;
	}
	
	return true;
}

bool GarageController::GarageStateMachine_AFechar_behavior(StateBehaviorEnum behavior, Signal* signal) 
{
	switch (behavior) {
		case ENTRY:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Entry Behavior: " << "GarageStateMachine_AFechar " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
		case DO:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Do Behavior: " << "GarageStateMachine_AFechar " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
		case EXIT:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Exit Behavior: " << "GarageStateMachine_AFechar " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
	}
	
	return true;
}

bool GarageController::GarageStateMachine_Aberta(StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount)
{
	if (!m_StateMachineImpl)
		return false;
	
	StateData*  state = m_StateMachineImpl->GetStateObject(submachineState, GarageController_ENUM_GARAGESTATEMACHINE_ABERTA);
	switch (behavior) {
		case ENTRY:
			if(state->active_count > 0)
				return false;
			m_garagestatemachine = GarageController_ENUM_GARAGESTATEMACHINE_ABERTA;
			state->IncrementActiveCount();
			GarageStateMachine_Aberta_behavior(ENTRY, signal);
			
			GarageStateMachine_Aberta_behavior(DO, signal);
			if((enumEntryType == EntryPointEntry || enumEntryType == DefaultEntry) && state->IsActiveState())
				m_StateMachineImpl->deferInternalEvent(COMPLETION, 0, state);
			break;
		case EXIT:
			if(state->active_count == 0)
				return false;
			m_garagestatemachine = NOSTATE;
			state->DecrementActiveCount();
			GarageStateMachine_Aberta_behavior(EXIT, signal);
			m_StateMachineImpl->removeInternalEvent(state);
			break;
	}
	
	return true;
}

bool GarageController::GarageStateMachine_Aberta_behavior(StateBehaviorEnum behavior, Signal* signal) 
{
	switch (behavior) {
		case ENTRY:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Entry Behavior: " << "GarageStateMachine_Aberta " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
		case DO:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Do Behavior: " << "GarageStateMachine_Aberta " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
		case EXIT:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Exit Behavior: " << "GarageStateMachine_Aberta " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
	}
	
	return true;
}

bool GarageController::GarageStateMachine_Fechada(StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount)
{
	if (!m_StateMachineImpl)
		return false;
	
	StateData*  state = m_StateMachineImpl->GetStateObject(submachineState, GarageController_ENUM_GARAGESTATEMACHINE_FECHADA);
	switch (behavior) {
		case ENTRY:
			if(state->active_count > 0)
				return false;
			m_garagestatemachine = GarageController_ENUM_GARAGESTATEMACHINE_FECHADA;
			state->IncrementActiveCount();
			GarageStateMachine_Fechada_behavior(ENTRY, signal);
			
			GarageStateMachine_Fechada_behavior(DO, signal);
			if((enumEntryType == EntryPointEntry || enumEntryType == DefaultEntry) && state->IsActiveState())
				m_StateMachineImpl->deferInternalEvent(COMPLETION, 0, state);
			break;
		case EXIT:
			if(state->active_count == 0)
				return false;
			m_garagestatemachine = NOSTATE;
			state->DecrementActiveCount();
			GarageStateMachine_Fechada_behavior(EXIT, signal);
			m_StateMachineImpl->removeInternalEvent(state);
			break;
	}
	
	return true;
}

bool GarageController::GarageStateMachine_Fechada_behavior(StateBehaviorEnum behavior, Signal* signal) 
{
	switch (behavior) {
		case ENTRY:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Entry Behavior: " << "GarageStateMachine_Fechada " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
		case DO:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Do Behavior: " << "GarageStateMachine_Fechada " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
		case EXIT:
		{
			StringStream ss;
			ss << "[" << m_sInstanceName << ":" << m_sType << "] Exit Behavior: " << "GarageStateMachine_Fechada " << endl;
			GlobalFuncs::trace(ss.str());
		}
			break;
	}
	
	return true;
}

bool GarageController::dispatch(Event* event, StateData* toState, bool bCheckOnly) 
{
	if (!m_StateMachineImpl)
		return false;
	
	bool bDispatched = false;
	
	if(!toState || !toState->IsActiveState() && !bCheckOnly)
		return bDispatched;
	
	switch (toState->state_enum) {
		case GarageController_VIRTUAL_SUBMACHINESTATE:
			if(event->eventEnum == COMPLETION)
			{
				if(!bCheckOnly)
				{
					m_StateMachineImpl->ReleaseSubmachineState(toState);
					for (list<StateData*>::iterator it = m_StateMachineImpl->lstStateData.begin(); it != m_StateMachineImpl->lstStateData.end(); )
					{
						StateData* state = *it;
						if (state == toState)
						{
							it = m_StateMachineImpl->lstStateData.erase(it);
							break;
						}
						else
							++it;
					}
					delete toState;
					toState = NULL;
				}				
				bDispatched = true;
			}
			break;
		case GarageController_ENUM_GARAGESTATEMACHINE_AABRIR:
			switch (event->eventEnum) {
				case ENUM_FIMABERTURA:
					if(true) {
						if(!bCheckOnly)
							TransitionProc(GarageController_ENUM_AABRIR__TO__ABERTA_4, event->signal, toState->submachine_state);
						bDispatched = true;
						break;
					}
					break;
		
			}
			break;
		case GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR:
			switch (event->eventEnum) {
				case ENUM_OBSTACLE:
					if(true) {
						if(!bCheckOnly)
							TransitionProc(GarageController_ENUM_AFECHAR__TO__AABRIR_7, event->signal, toState->submachine_state);
						bDispatched = true;
						break;
					}
					break;
				case ENUM_FIMFECHO:
					if(true) {
						if(!bCheckOnly)
							TransitionProc(GarageController_ENUM_AFECHAR__TO__FECHADA_6, event->signal, toState->submachine_state);
						bDispatched = true;
						break;
					}
					break;
		
			}
			break;
		case GarageController_ENUM_GARAGESTATEMACHINE_ABERTA:
			switch (event->eventEnum) {
				case ENUM_BOTAOPREMIDO:
					if(NoObstacle) {
						if(!bCheckOnly)
							TransitionProc(GarageController_ENUM_ABERTA__TO__AFECHAR_5, event->signal, toState->submachine_state);
						bDispatched = true;
						break;
					}
					break;
		
			}
			break;
		case GarageController_ENUM_GARAGESTATEMACHINE_FECHADA:
			switch (event->eventEnum) {
				case ENUM_BOTAOPREMIDO:
					if(true) {
						if(!bCheckOnly)
							TransitionProc(GarageController_ENUM_FECHADA__TO__AABRIR_3, event->signal, toState->submachine_state);
						bDispatched = true;
						break;
					}
					break;
		
			}
			break;
	}
	
	if(!bDispatched && toState && toState->parent_state && event->eventEnum != COMPLETION)
	{
		bDispatched = dispatch(event, toState->parent_state, true);
		if(bDispatched && !bCheckOnly)
		{
			/*1. Exit the current state; 2. Decrement the active count of the parent state; 3. dispatch the event to parent state*/
			StateProc((StateEnum)toState->state_enum, toState->submachine_state, EXIT, 0);
			toState->parent_state->DecrementActiveCount();
			dispatch(event, toState->parent_state, false);
			event = 0;
		}
	}
	
	return bDispatched;
}

void GarageController::runStateMachine(StateMachineEnum statemachine) 
{
	if (!m_StateMachineImpl)
		return;
	
	list<StateData*> activeStateArray;
	if(m_StateMachineImpl->GetCurrentStates(activeStateArray) > 0)
		return;
	
	switch (statemachine) {
		case GarageController_ENUM_GARAGESTATEMACHINE:
			{
			}
			break;
	}
}

void GarageController::runStateMachines()
{
	runStateMachine(GarageController_ENUM_GARAGESTATEMACHINE);
}

void GarageController::runStateMachine(String statemachine)
{
	if(statemachine == "GarageController_GarageStateMachine")
	{
		runStateMachine(GarageController_ENUM_GARAGESTATEMACHINE);
		return;
	}
}

void GarageController::runStateMachine(StateMachineEnum statemachine, StateData* submachineState, Signal* signal, EntryEnum entryArray[], int nEntryCount) 
{
	if(!submachineState)
	{
		StateInitialData initialData(GarageController_VIRTUAL_SUBMACHINESTATE, NOSTATE, 1, false, "GarageController_VIRTUAL_SUBMACHINESTATE", "", ""); 
		submachineState = new StateData(m_StateMachineImpl, &initialData);
		
		submachineState->IncrementActiveCount();
		m_StateMachineImpl->lstStateData.push_back(submachineState);
	}
	switch (statemachine) {
		case GarageController_ENUM_GARAGESTATEMACHINE:
			{
				const int nArrayCount = 4;
				StateInitialData initialDataArray[nArrayCount] = 
					{
						StateInitialData(GarageController_ENUM_GARAGESTATEMACHINE_AABRIR, NOSTATE, 0, false, "GarageController_GarageStateMachine_AAbrir", "{F3E8432A-1439-4a61-B154-00B4E2032CAB}", m_sInstanceName),
						StateInitialData(GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR, NOSTATE, 0, false, "GarageController_GarageStateMachine_AFechar", "{D18CD5B3-7167-4a29-A923-FF659BC4DA55}", m_sInstanceName),
						StateInitialData(GarageController_ENUM_GARAGESTATEMACHINE_ABERTA, NOSTATE, 0, false, "GarageController_GarageStateMachine_Aberta", "{D97A77B3-9577-4375-8BE5-053D37E9D26E}", m_sInstanceName),
						StateInitialData(GarageController_ENUM_GARAGESTATEMACHINE_FECHADA, NOSTATE, 0, false, "GarageController_GarageStateMachine_Fechada", "{39181682-7B69-4df0-8F24-CC8AC5932414}", m_sInstanceName)
					};
		
				m_StateMachineImpl->CreateStateObjects(initialDataArray, nArrayCount, submachineState);
			}
			for(int i = 0; i < nEntryCount; i++)
			{
				switch(entryArray[i])
				{
				case GarageController_ENUM_GARAGESTATEMACHINE_ENTRYPOINT_5_5:
					TransitionProc(GarageController_ENUM_ENTRYPOINT_5_5__TO__FECHADA_2, signal, submachineState);
					break;
				}
			}
			if(submachineState->IsActiveState())
				m_StateMachineImpl->deferInternalEvent(COMPLETION, 0, submachineState);
			break;
	}
}

String GarageController::GetInstanceName()
{
	return m_sInstanceName;
}

String GarageController::GetTypeName()
{
	return m_sType;
}







/* End - EA generated code for StateMachine */