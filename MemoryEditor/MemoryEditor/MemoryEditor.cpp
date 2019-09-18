// MemoryEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment( lib, "psapi.lib" )
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

#define UNICODE
#include <Windows.h>
#include <stdio.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <string>
#include "ProcessHelper.h"
#include <sstream>

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
	/*
	wprintf(L"Start:\n");
	HANDLE hndl = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE, 0);
	if (hndl)
	{
		PROCESSENTRY32  process = { sizeof(PROCESSENTRY32) };
		
		Process32First(hndl, &process);
		
		do
		{
			//process.szExeFile
			wprintf(L"%8u, %s\n", process.th32ProcessID, process.szExeFile);
		} while (Process32Next(hndl, &process));

		CloseHandle(hndl);
	}
	*/

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
	
	uintptr_t base = GetModuleBase(st);

	std::cout << "[Log] The Base Address - " << std::hex << "0x" << base << std::endl;


	//Get Handle to Process
	DWORD procID = GetProcessID(st);
	HANDLE hProcess = nullptr;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

	return hProcess;
}

int main()
{
    std::cout << "Hello World!\n";
	HANDLE handle = nullptr;
	int userInput = 0;
	while (userInput != 9 && handle == nullptr)
	{
		system("cls");
		std::cout << "===============================" << std::endl;
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
		
		TCHAR buffer[MAX_PATH];
		GetModuleFileNameEx(handle, NULL, buffer, sizeof(buffer) / sizeof(TCHAR));

		//std::cout << "name " << buffer << std::endl;
		_tprintf(TEXT("%s \n"), buffer);
		/*
		while (userInput != 9 )
		{
			

		}
		*/
	}
	else
	{
		
	}
	

	return 0;

	/*
		// Get the list of process identifiers.

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
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

	return 0;
	*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
