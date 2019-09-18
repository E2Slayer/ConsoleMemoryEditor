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
