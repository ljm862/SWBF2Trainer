#pragma once
#include <Windows.h>
#include <vector>

namespace mem {

	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void Nop(BYTE* dst, unsigned int size);
	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int>offsets);

	bool Detour32(BYTE* src, BYTE* dest, const uintptr_t len);
	BYTE* TrampolineHook32(BYTE* src, BYTE* dest, const uintptr_t len);
}