// MemoryEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment( lib, "psapi.lib" )
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <psapi.h>

#include <string>
#include "ProcessHelper.h"
#include <sstream>
#include "ReadWrite.h"


uintptr_t g_ModuleBase = 0;

// Code from https://docs.microsoft.com/en-us/windows/win32/psapi/enumerating-all-processes
// To ensure correct resolution of symbols, add Psapi.lib to TARGETLIBS
// and compile with -DPSAPI_VERSION=1

void PrintProcessNameAndID(DWORD processID)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	// Get a handle to the process.

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	// Get the process name.

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}
	}

	// Print the process name and identifier.
	if (_tcscmp(szProcessName, TEXT("<unknown>")) != 0)
	{
		_tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);
	}

	// Release the handle to the process.

	CloseHandle(hProcess);
}



void Enum_Processes()
{
	system("cls"); // clear the console
	std::cout << "===============================" << std::endl;
	std::cout << "List of the Current Processes" << std::endl;
	std::cout << "===============================" << std::endl;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return;
	}


	// Calculate how many process identifiers were returned.

	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.

	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			PrintProcessNameAndID(aProcesses[i]);
		}
	}
	std::cout << "===============================" << std::endl;
	std::cout << "Enter 1 to Go Back" << std::endl;
	std::cout << "===============================" << std::endl;
	int userInput = 0;
	while (userInput != 1)
	{
		std::cin >> userInput;
	}
}

HANDLE Attach_Process()
{
	system("cls");
	std::cout << "===============================" << std::endl;
	std::cout << "Attach a Process" << std::endl;
	std::cout << "===============================" << std::endl;
	/*
	DWORD userInput = 0;
	std::cout << "Please, enter a PID : ";
	std::cin >> userInput;
	*/
	std::string pName;
	std::cout << "Enter a Process Name : ";
	std::cin >> pName;
	std::wstring widestr = std::wstring(pName.begin(), pName.end());
	const wchar_t* st = widestr.c_str();
	
	g_ModuleBase = GetModuleBase(st);
	//g_ModuleBase = base;
	std::cout << "[Log] The Base Address - " << std::hex << "0x" << g_ModuleBase << std::endl;


	//Get Handle to Process
	DWORD procID = GetProcessID(st);
	HANDLE hProcess = nullptr;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

	return hProcess;
}

int main()
{
	HANDLE handle = nullptr;
	int userInput = 0;
	while (userInput != 9 && handle == nullptr)
	{
		system("cls");
		std::cout << "===============================" << std::endl;
		std::cout << "0 : Display a list of processes" << std::endl;
		std::cout << "1 : Attach a Process" << std::endl;
		std::cout << "===============================" << std::endl;
		std::cout << "9 : Exit" << std::endl;
		std::cout << "===============================" << std::endl;
		std::cout << "Please, enter a number : ";
		std::cin >> userInput;

		switch (userInput)
		{
		case 0:
			Enum_Processes();
			break;
		case 1:
			system("cls");
			std::cout << "===============================" << std::endl;
			std::cout << "Log" << std::endl;
			std::cout << "===============================" << std::endl;
			handle = Attach_Process();
			break;
		default:
			break;
		}

	}

	if(handle)
	{

		// Display the file directory of the current attached handle 
		TCHAR buffer[MAX_PATH];
		GetModuleFileNameEx(handle, NULL, buffer, sizeof(buffer) / sizeof(TCHAR));
		std::cout << "===============================" << std::endl;
		std::cout << "Attached File" << std::endl;
		std::cout << "===============================" << std::endl;
		_tprintf(TEXT("%s \n"), buffer);
		std::cout << "===============================" << std::endl;
		userInput = 0;

		while (userInput != 9)
		{
			std::cout << "===============================" << std::endl;
			std::cout << "0 : Memory Search" << std::endl;
			std::cout << "1 : Read Memory" << std::endl;
			std::cout << "2 : Write Memory" << std::endl;
			std::cout << "3 : Saved List" << std::endl;
			std::cout << "===============================" << std::endl;
			std::cout << "9 : Exit" << std::endl;
			std::cout << "===============================" << std::endl;
			std::cout << "Please, enter a number : ";
			std::cin >> userInput;
			uintptr_t temp = g_ModuleBase + 0x4f;
			//ReadMemory(handle, 0, temp);
			switch (userInput)
			{
			case 0:
				break;
			case 1:
				ProcessReadMemory(handle, g_ModuleBase);
				break;
			case 2:
				ProcessWriteMemory(handle, g_ModuleBase);
				break;
			case 3:

				break;
			default:
				break;
			}
		}

	}
	else
	{
		
	}
	
	CloseHandle(handle);
	return 0;
}
