#include <stdio.h>
#include "..\\Lab6DLL\Containers.h"

void* Allc(size_t s)
{
	return malloc(s);
}

void Deallc(void* p)
{
	free(p);
}

void main(void)
{
	AssociativeArray* arr = new_AssociativeArray(Allc, Deallc);
	for (int i = 0; i < 32; i++)
	{
		int sq = i * i;
		addKeyValue_AssociativeArray(&i, sizeof(i), &sq, sizeof(sq), arr);
	}
	for (int i = 0; i < 32; i++)
	{
		Pair* p = at_AssociativeArray(&i, sizeof(i), arr);
		printf("k: %04d\tv: %04d\n", *(int*)p->key_ptr, *(int*)p->value_ptr);
	}
	del_AssociativeArray(arr);
}