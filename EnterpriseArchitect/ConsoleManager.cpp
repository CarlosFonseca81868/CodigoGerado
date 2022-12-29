#include "ConsoleManager.h"
#include <time.h>
using namespace std;

ConsoleManager::ConsoleManager(){
	Part1 = new GarageController(this, "Part1");
	lstContext.push_back(Part1->m_StateMachineImpl);
	//setup instance associations
}

void ConsoleManager::ClearInstance(String instanceStr)
{
	if(instanceStr.compare("Part1") == 0)
		Part1 = NULL;
}

void ConsoleManager::Run()
{
	simulationStartTime = GetTickCount();	//Windows Only
	bool bContinue=true;
	RunAllStateMachines();
	while(bContinue)
	{
		//recall all completion events
		EvaluateCommandString("stepall");
		
		String in;
		getline(cin, in);
		bContinue = EvaluateCommandString(in);
	}
}

/*
int main() {
	ConsoleManager manager;
	manager.initialize();
	manager.Run();
	return 0;
}
*/