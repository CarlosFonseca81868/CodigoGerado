#include "EventProxy.h"


using namespace std;
template <typename T>
T StringToNumber ( const String &Text )
{
	StringStream ss(Text);
	T result;
	return ss >> result ? result : 0;
}



void ReleaseSignal(Signal* signal)
{
	if(signal)
	{
		signal->nReferenceCount--;
		if(signal->nReferenceCount <= 0)
			delete signal;
	}		
}

void AddSignalReference(Signal* signal)
{
	if(signal)
	{
		signal->nReferenceCount++;
	}
}

void ReleaseEvent(Event* event)
{
	if(event)
	{
		event->nReferenceCount--;
		if(event->nReferenceCount <= 0)
			delete event;
	}
}

void AddEventReference(Event* event)
{
	if(event)
	{
		event->nReferenceCount++;
	}
}

Event::Event(EventEnum eventEnum_, Signal* signal_)
{
	nReferenceCount = 0;
	
	eventEnum = eventEnum_;
	signal = signal_;
	
	AddSignalReference(signal);
}

Event::~Event()
{
	ReleaseSignal(signal);
}

Signal* GetSignalInstance( String signalStr, std::vector<String>& arguments)
{
	Signal* signal = NULL;
	while(true)
	{
	
		break;
	}
	return signal;
}

StringTable::StringTable()
{
	mapStringToEventEnum["FimFecho"] = ENUM_FIMFECHO;
	mapStringToEventEnum["Obstacle"] = ENUM_OBSTACLE;
	mapStringToEventEnum["FimAbertura"] = ENUM_FIMABERTURA;
	mapStringToEventEnum["BotaoPremido"] = ENUM_BOTAOPREMIDO;
	mapStringToEventEnum["BotaoPremido"] = ENUM_BOTAOPREMIDO;	
	mapEventEnumToString[ENUM_FIMFECHO] = "FimFecho";
	mapEventEnumToString[ENUM_OBSTACLE] = "Obstacle";
	mapEventEnumToString[ENUM_FIMABERTURA] = "FimAbertura";
	mapEventEnumToString[ENUM_BOTAOPREMIDO] = "BotaoPremido";
	mapEventEnumToString[ENUM_BOTAOPREMIDO] = "BotaoPremido";
	mapNameToGuid["FimFecho"] = "{299F01A4-E4A1-4a33-AF87-294187B75DE7}";
	mapNameToGuid["Obstacle"] = "{3E15DC35-01C1-432d-9B6C-188421503B8F}";
	mapNameToGuid["FimAbertura"] = "{5D3A1DCC-B598-4d96-AE8C-71BC76DEEF1B}";
	mapNameToGuid["BotaoPremido"] = "{B9F4BF91-F13E-4133-B80D-97F5719A9894}";
	mapNameToGuid["BotaoPremido"] = "{D2F6E541-DA81-4fe6-9182-0B3B2FCDE75D}";
}
StringTable StringTable::stringTable;