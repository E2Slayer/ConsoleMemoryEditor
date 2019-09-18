#pragma once
#include <windows.h>
#include <cstdint>

void ReadMemory(HANDLE& handle, uintptr_t moduleBase, uintptr_t& address);
