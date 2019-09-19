#pragma once
#include <windows.h>
#include <cstdint>

void ReadMemory(HANDLE& handle, uintptr_t moduleBase, uintptr_t& address);
void ProcessReadMemory(HANDLE& handle, uintptr_t moduleBase);

void WriteMemory(HANDLE& handle, uintptr_t moduleBase, uintptr_t& address, int& input);
void ProcessWriteMemory(HANDLE& handle, uintptr_t moduleBase);