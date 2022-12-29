#pragma once
#include <iostream>
#include <list>
#include <map>
#include <deque>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
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
class Signal;
enum SignalEnum 
{
	EMPTY,
};

enum EventEnum 
{
	COMPLETION,
	ENUM_FIMFECHO,
	ENUM_OBSTACLE,
	ENUM_FIMABERTURA,
	ENUM_BOTAOPREMIDO,
	ENUM_BOTAOPREMIDO
};

class Signal 
{
public:
	Signal()
	{
		nReferenceCount = 0;
	}
	SignalEnum signalEnum;
	int nReferenceCount;
	
	std::vector<String> parameters;
	std::map<String, String> parameterValues;
};

class Event {
public:
	Event(EventEnum eventEnum_, Signal* signal_);
	virtual ~Event();
	EventEnum eventEnum;
	Signal* signal;
	int nReferenceCount;
};

void ReleaseSignal(Signal* signal);
void AddSignalReference(Signal* signal);
void ReleaseEvent(Event* event);
void AddEventReference(Event* event);
Signal* GetSignalInstance( String signalStr, std::vector<String>& arguments);
class StringTable {
public:
	StringTable();
	std::map<String,EventEnum> mapStringToEventEnum;
	std::map<EventEnum, String> mapEventEnumToString;
	std::map<SignalEnum, String> mapSignalEnumToString;
	std::map<String, String> mapNameToGuid;
	static StringTable stringTable;	
};

	