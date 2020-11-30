#include "includes.h"

void mem::Patch(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void mem::Nop(BYTE* dst, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

uintptr_t mem::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i) {
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}
	return addr;
}

bool mem::Detour32(BYTE* src, BYTE* dest, const uintptr_t len)
{
	if (len < 5) return false;

	DWORD curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);
	memset(src, 0x90, len);
	uintptr_t relativeAddress = (uintptr_t)(dest - src - 5);
	*src = (BYTE)0xE9;
	*(uintptr_t*)(src + 1) = relativeAddress;

	VirtualProtect(src, len, curProtection, &curProtection);
	return true;
}

BYTE* mem::TrampolineHook32(BYTE* src, BYTE* dest, const uintptr_t len)
{
	if (len < 5) return 0;

	//Create the Gateway
	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	//Write the bytes we're replacing with jump to the gateway
	memcpy(gateway, src, len);

	//Get the relative address from gateway to original
	uintptr_t relativeAddress = src - gateway - 5;

	//Setup the jump details
	*(gateway + len) = 0xE9;
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = relativeAddress;

	//Call the base detour
	return Detour32(src, dest, len) ? gateway : nullptr;
}