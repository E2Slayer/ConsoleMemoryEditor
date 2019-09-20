#pragma once
#include <cstdint>
#include <string>
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <psapi.h>


enum Types
{
	None, Byte, Byte2, Byte4
};


class AddressInfo
{
public:
	std::string description = "No Description";
	uintptr_t address = 0x0;
	Types type = Types::None;


	AddressInfo();
};

