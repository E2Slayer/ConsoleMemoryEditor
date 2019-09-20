#include "ReadWrite.h"

#include <windows.h>
#include <iostream>
#include <vector>
#include "SavedList.h"


void ReadMemory(HANDLE &handle, uintptr_t &address)
{
	//Read Ammo value
	int value = 0;

	ReadProcessMemory(handle, (BYTE*)address, &value, sizeof(value), nullptr);
	std::cout << "Read Memory = " << std::dec << value << std::endl;

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
	ReadMemory(handle, temp);
	// TODO add as hex not decimal 
	SaveAddress(temp);
	
}

void WriteMemory(HANDLE& handle, uintptr_t& address, int &input)
{
	//Read Ammo value
	int value = input;



	DWORD oldProtect = 0;
	DWORD numRead = 0;
	VirtualProtectEx(handle, (BYTE*)address, 256, PAGE_EXECUTE_READWRITE, &oldProtect);

	
	WriteProcessMemory(handle, (BYTE*)address, &value, sizeof(value), nullptr);
	//std::cout << "Input = " << std::dec << input << std::endl;
	ReadMemory(handle, address);

	VirtualProtectEx(handle, (BYTE*)address, 256, oldProtect, nullptr);


}

void ProcessWriteMemory(HANDLE& handle, uintptr_t moduleBase)
{
	system("cls");
	//uintptr_t temp = g_ModuleBase + 0x4f;

	int userinput = 0;

	std::cout << "0 - Based on modulebase / 1 - Based on a custom address : ";
	std::cin >> std::dec >> userinput;

	
	
	uintptr_t add = 0;
	std::cout << "Please, enter an address : ";
	std::cin >> std::hex >> add;
	//std::cout << "0x" << std::hex << moduleBase << " + 0x" << std::hex << add << std::endl;

	if(userinput == 0)
	{
		std::cout << "0x" << std::hex << moduleBase << " + 0x" << std::hex << add << std::endl;
		add += moduleBase;
		//std::cout << "0x" << std::hex << moduleBase << " + 0x" << std::hex << add << std::endl;
	}
	else
	{
		std::cout << "0x" << std::hex << add << std::endl;
	}


	userinput = -1;

	std::cout << "Is it a multi-leveled pointer? (0: Yes / 1: No) : ";
	std::cin >> std::dec >> userinput;
	std::vector<uintptr_t> container;
	if(userinput == 0)
	{
		int loop = 0;

		std::cout << "How many levels ? : ";
		std::cin >> std::dec >> loop;
		
		for(int i=0; i<loop; ++i)
		{
			uintptr_t inside = 0;
			std::cout << "Please, enter pointer(" << i+1 <<") address: ";
			std::cin >> std::hex >> inside;
			container.push_back(inside);
		}
		add = MultiLevelPointer(handle, add, container);
		std::cout << "Final Pointer Address : " << std::hex << add << std::endl;
	}
	
//	uintptr_t temp = moduleBase + add;

	int value = 0;
	std::cout << "Please, enter a new value : ";
	std::cin >> std::dec >> value;
	WriteMemory(handle, add, value);
	// TODO add as hex not decimal

	SaveAddress(add);

}

void SaveAddress(uintptr_t add)
{
	int value = 0;
	std::cout << "Do you want to save it? (0: Yes / 1: No) : ";
	std::cin >> std::dec >> value;

	if(value == 0)
	{
		auto t = SavedList();
		t.SaveAnAddress(add, "test", Types::Byte4);
		//SavedList::SaveAnAddress(add, "test", Types::Byte4);
	}
}

uintptr_t MultiLevelPointer(HANDLE handle, uintptr_t address, const std::vector<uintptr_t> &levels)
{
	uintptr_t result = 0;

	for(uintptr_t add : levels)
	{
		ReadProcessMemory(handle, (BYTE*)address, &result, sizeof(result), nullptr);
		result += add;
	}
	return result;
}

