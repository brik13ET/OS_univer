#include <stdio.h>
#include "..\\Lab6DLL\Containers.h" // Path to dll header

// неявное
void* Allc(size_t s)
{
	HANDLE h = GetProcessHeap();
	return (void*)HeapAlloc(h, 0, s);
}

void Deallc(void* p)
{
	return HeapFree(GetProcessHeap(), 0, (LPVOID)p);
}

void main(void)
{
	AssociativeArray* arr = new_AssociativeArray(Allc, Deallc);
	for (int i = 0; i < 10; i++)
	{
		int sq = i * i;
		addKeyValue_AssociativeArray(&i, sizeof(i), &sq, sizeof(sq), arr);
	}
	for (int i = 0; i < 10; i++)
	{
		Pair* p = at_AssociativeArray(&i, sizeof(i), arr);
		printf("k: %04d\tv: %04d\n", *(int*)p->key_ptr, *(int*)p->value_ptr);
	}
	del_AssociativeArray(arr);
}