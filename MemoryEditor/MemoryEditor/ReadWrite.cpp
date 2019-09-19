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
	std::cin >> std::hex >> add;
	std::cout << "0x" << std::hex << moduleBase << " + 0x" << std::hex << add << std::endl;
	uintptr_t temp = moduleBase + add;
	ReadMemory(handle, 0, temp);
	// TODO add as hex not decimal 

	
}

void WriteMemory(HANDLE& handle, uintptr_t moduleBase, uintptr_t& address, int &input)
{
	//Read Ammo value
	int value = input;



	DWORD oldProtect = 0;
	DWORD numRead = 0;
	VirtualProtectEx(handle, (BYTE*)address, 256, PAGE_EXECUTE_READWRITE, &oldProtect);

	
	WriteProcessMemory(handle, (BYTE*)address, &value, sizeof(value), nullptr);
	std::cout << "Input = " << std::dec << input << std::endl;
	ReadMemory(handle, 0, address);

	VirtualProtectEx(handle, (BYTE*)address, 256, oldProtect, NULL);


}

void ProcessWriteMemory(HANDLE& handle, uintptr_t moduleBase)
{
	system("cls");
	//uintptr_t temp = g_ModuleBase + 0x4f;
	uintptr_t add = 0;
	std::cout << "Please, enter an address : ";
	std::cin >> std::hex >> add;
	std::cout << "0x" << std::hex << moduleBase << " + 0x" << std::hex << add << std::endl;
	uintptr_t temp = moduleBase + add;

	int value = 0;
	std::cout << "Please, enter a new value : ";
	std::cin >> std::dec >> value;
	WriteMemory(handle, 0, temp, value);
	// TODO add as hex not decimal 


}