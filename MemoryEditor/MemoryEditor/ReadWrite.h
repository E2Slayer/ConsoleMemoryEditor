#pragma once
#include <windows.h>
#include <cstdint>
#include <vector>

void ReadMemory(HANDLE& handle, uintptr_t& address);
void ProcessReadMemory(HANDLE& handle, uintptr_t moduleBase);

void WriteMemory(HANDLE& handle, uintptr_t& address, int& input);
void ProcessWriteMemory(HANDLE& handle, uintptr_t moduleBase);

void SaveAddress(uintptr_t add);

uintptr_t MultiLevelPointer(HANDLE handle, uintptr_t address, const std::vector<uintptr_t>& levels);

