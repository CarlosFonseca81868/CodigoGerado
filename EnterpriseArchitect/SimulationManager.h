#pragma once
#include "ContextManager.h"
#include "Garage Controller.h"
class SimulationManager : public ContextManager
{
public:
	GarageController* Part1;
public:
	SimulationManager();
	virtual ~SimulationManager();
	
	TCHAR* m_pCommand;
	std::deque<String> m_commands;

	
	void ClearInstance(String instanceStr);
	void Run();

	
	String GetStatePath(StateData*);
	void SetActiveStates();
	void ClearActiveStates();
	String*	activeStates[MAX_STATES];
	int activeStateCount;

	bool Dequeue( String&  );
	void OnStepComplete();	
};