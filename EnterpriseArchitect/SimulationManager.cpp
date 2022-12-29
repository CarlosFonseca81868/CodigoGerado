#include "SimulationManager.h"
#include <time.h>
using namespace std;

SimulationManager::SimulationManager(){
	Part1 = new GarageController(this, "Part1");
	lstContext.push_back(Part1->m_StateMachineImpl);
	//setup instance associations
	m_pCommand = new TCHAR[ SHARED_MEMORY_STRING_LENGTH ];
	*m_pCommand = 0;
	
	for(int i = 0; i < MAX_STATES; i++)
	{
		activeStates[i] = NULL;
	}
	activeStateCount=0;
}

SimulationManager::~SimulationManager(){
	if(m_pCommand)
	{
		delete[] m_pCommand;
		m_pCommand = NULL;
	}
}

void SimulationManager::ClearInstance(String instanceStr)
{
	if(instanceStr.compare("Part1") == 0)
		Part1 = NULL;
}

void SimulationManager::Run()
{
	simulationStartTime = GetTickCount();	//Windows Only
	
	bool bContinue=true;
	RunAllStateMachines();
	while(bContinue)
	{
		SetActiveStates();
		
		///////////////////
		OnStepComplete();
		///////////////////
		String in;
		Dequeue(in);
		bContinue = EvaluateCommandString(in);
	}
}

String SimulationManager::GetStatePath( StateData* pState)
{
	String strPath;
	
	std::vector<String> names;
	StateData* parent = pState;
	while(parent)
	{
		if(!parent->state_guid.empty())
		{
			names.push_back(parent->state_guid);
		}
		parent = parent->parent_state;
	}
	std::vector<String>::reverse_iterator prev = names.rbegin();
	while(prev != names.rend())
	{
		if(!strPath.empty())
		{
			strPath += _T(",");
		}			
		strPath += *prev;
		prev++;
	}
	return strPath;
}

void SimulationManager::SetActiveStates()
{
	ClearActiveStates();
	
	for (list<StateMachineImpl*>::iterator it = lstContext.begin(); it != lstContext.end(); it++)
	{
		StateMachineImpl* pContext = *it;
		if(pContext)
		{
			list<StateData*>* pList = pContext->GetStateData();
			if(pList)
			{
				for (list<StateData*>::iterator it2 = pList->begin(); it2 != pList->end(); it2++)
				{
					StateData* pState = *it2;
					if(pState && pState->active_count == 1)
					{
						String* pStatePath = new String(pContext->GetInstanceName() + "," + GetStatePath(pState));
						activeStates[ activeStateCount++ ] = pStatePath;
					}
				}
			}
		}
	}
}

void SimulationManager::ClearActiveStates()
{
	for(int i = 0; i < activeStateCount; i++)
	{
		String* pString =  activeStates[i];
		if(pString)
		{
			delete pString;
			activeStates[i] = NULL;
		}
	}
	activeStateCount = 0;
}

bool SimulationManager::Dequeue( String& strTrigger )
{
	if(!m_commands.empty())
	{
		strTrigger = m_commands.front();
		m_commands.pop_front();
		return true;
	}
	return false;
}

void SimulationManager::OnStepComplete()
{
	// Synchronization point for EA
	if(m_pCommand && *m_pCommand)
	{
		String strTrigger( m_pCommand );
		m_commands.push_back(  strTrigger );
		*m_pCommand=0;
	}
}

int main() {
	SimulationManager manager;
	manager.initialize();
	manager.Run();
	return 0;
}