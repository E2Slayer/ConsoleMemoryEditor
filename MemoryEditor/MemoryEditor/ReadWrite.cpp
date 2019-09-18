#include "ReadWrite.h"

#include <windows.h>
#include <iostream>




void ReadMemory(HANDLE &handle, uintptr_t moduleBase, uintptr_t &address)
{
	//Read Ammo value
	int value = 0;

	ReadProcessMemory(handle, (BYTE*)address, &value, sizeof(value), nullptr);
	std::cout << "Memory = " << std::dec << value << std::endl;

}

void ProcessReadMemory(HANDLE& handle, uintptr_t moduleBase)
{
	system("cls");
	//uintptr_t temp = g_ModuleBase + 0x4f;
	uintptr_t add = 0;
	std::cout << "Please, enter an address : ";
	std::cin >> add;
	std::cout << "0x" << std::hex << moduleBase << " + 0x" << std::hex << add << std::endl;
	uintptr_t temp = moduleBase + add;
	ReadMemory(handle, 0, temp);
	// TODO add as hex not decimal 

	
}