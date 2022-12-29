///////////////////////////////////////////////////////////
//  Garage Controller.h
//  Implementation of the Class Garage Controller
//  Created on:      15-jun-2022 14:58:38
//  Original author: Carlos
///////////////////////////////////////////////////////////

#if !defined(EA_FEFB4E94_A291_4636_A6A9_A20B1377683B__INCLUDED_)
#define EA_FEFB4E94_A291_4636_A6A9_A20B1377683B__INCLUDED_

#include "ContextManager.h"
#include "StmCommonForwardDeclaration.h"
#include "Class B.h"

class Garage Controller : public StateMachineContext
{

public:
	Class B *m_Class B;

	void abrir();
	void BotaoPremido();
	void fechar();
	void fim_stop();
	void stop();
	void stop_fecho();

private:
	Boolean NoObstacle;

	/* Begin - EA generated code for StateMachine */






public:
	enum StateMachineEnum 
	{
		NOSTATEMACHINE,
		GarageController_ENUM_GARAGESTATEMACHINE
	};

	enum StateEnum 
	{
		NOSTATE,
		GarageController_VIRTUAL_SUBMACHINESTATE,
		GarageController_ENUM_GARAGESTATEMACHINE_AABRIR,
		GarageController_ENUM_GARAGESTATEMACHINE_AFECHAR,
		GarageController_ENUM_GARAGESTATEMACHINE_ABERTA,
		GarageController_ENUM_GARAGESTATEMACHINE_FECHADA
	};

	enum TransitionEnum 
	{
		NOTRANSITION,
		GarageController_ENUM_ABERTA__TO__AFECHAR_5,
		GarageController_ENUM_FECHADA__TO__AABRIR_3,
		GarageController_ENUM_AFECHAR__TO__AABRIR_7,
		GarageController_ENUM_ENTRYPOINT_5_5__TO__FECHADA_2,
		GarageController_ENUM_AFECHAR__TO__FECHADA_6,
		GarageController_ENUM_AABRIR__TO__ABERTA_4
	};

	enum EntryEnum
	{
		NOENTRY,
		GarageController_ENUM_GARAGESTATEMACHINE_ENTRYPOINT_5_5
	};

	GarageController();
	GarageController(ContextManager* pManager, String sInstanceName);
	
	virtual ~GarageController();
	
	StateMachineImpl* m_StateMachineImpl;
	
    String m_sInstanceName;
    String m_sType;
	StateEnum m_garagestatemachine;
public:
	void TransitionProc(TransitionEnum transition, Signal* signal, StateData* submachineState);

	
	void Aberta__TO__AFechar_5_effect(Signal* signal);
	void Aberta__TO__AFechar_5(Signal* signal, StateData* submachineState);
	void Fechada__TO__AAbrir_3_effect(Signal* signal);
	void Fechada__TO__AAbrir_3(Signal* signal, StateData* submachineState);
	void AFechar__TO__AAbrir_7_effect(Signal* signal);
	void AFechar__TO__AAbrir_7(Signal* signal, StateData* submachineState);
	void entryPoint_5_5__TO__Fechada_2_effect(Signal* signal);
	void entryPoint_5_5__TO__Fechada_2(Signal* signal, StateData* submachineState);
	void AFechar__TO__Fechada_6_effect(Signal* signal);
	void AFechar__TO__Fechada_6(Signal* signal, StateData* submachineState);
	void AAbrir__TO__Aberta_4_effect(Signal* signal);
	void AAbrir__TO__Aberta_4(Signal* signal, StateData* submachineState);
	
	bool StateProc(StateEnum state, StateData* submachineState, StateBehaviorEnum behavior, Signal* signal, EntryTypeEnum enumEntryType = DefaultEntry, EntryEnum entryArray[] = NULL, int nArrayCount = 0);

	
	bool GarageStateMachine_AAbrir(StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount);
	bool GarageStateMachine_AAbrir_behavior(StateBehaviorEnum behavior, Signal* signal);
	bool GarageStateMachine_AFechar(StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount);
	bool GarageStateMachine_AFechar_behavior(StateBehaviorEnum behavior, Signal* signal);
	bool GarageStateMachine_Aberta(StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount);
	bool GarageStateMachine_Aberta_behavior(StateBehaviorEnum behavior, Signal* signal);
	bool GarageStateMachine_Fechada(StateBehaviorEnum behavior, StateData* submachineState, Signal* signal, EntryTypeEnum enumEntryType, EntryEnum entryArray[], int nArrayCount);
	bool GarageStateMachine_Fechada_behavior(StateBehaviorEnum behavior, Signal* signal);
	
	virtual void runStateMachines() ;
	virtual void runStateMachine(String statemachine);
	virtual void runStateMachine(StateMachineEnum statemachine);
	virtual void runStateMachine(StateMachineEnum statemachine, StateData* submachineState, Signal* signal, EntryEnum entryArray[] = NULL, int nEntryCount = 0);
	virtual bool StateProc(int state, StateData* submachineState, StateBehaviorEnum behavior, Signal* signal, EntryTypeEnum enumEntryType, int entryArray[], int nArrayCount);
	virtual bool dispatch(Event* event, StateData* toState, bool bCheckOnly);
	
	virtual bool defer(Event* event, StateData* toState);
	
	virtual String GetInstanceName();
	virtual String GetTypeName();




	/* End - EA generated code for StateMachine */

};
#endif // !defined(EA_FEFB4E94_A291_4636_A6A9_A20B1377683B__INCLUDED_)
