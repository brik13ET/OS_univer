#include "mem.h"

void* MyAlloc(size_t siz)
{
	HANDLE h = GetProcessHeap();
	return (void*)HeapAlloc(h, 0, siz);
}

BOOL MyFree(void* ptr)
{
	return HeapFree(GetProcessHeap(), 0, (LPVOID)ptr);
}

int MyMemcpy(void* _1, void* _2, size_t _3)
{
	return memcpy(_1, _2, _3);
}

int MyMemcmp(void* _1, void* _2, size_t _3)
{
	return memcmp(_1, _2, _3);
}
