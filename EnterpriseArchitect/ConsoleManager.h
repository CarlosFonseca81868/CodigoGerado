#pragma once
#include "ContextManager.h"
#include "Garage Controller.h"
class ConsoleManager : public ContextManager
{
public:
	GarageController* Part1;
public:
	ConsoleManager();
	void ClearInstance(String instanceStr);
	void Run();
};