#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define LAB6_ONLYTYPE
#include "..\\Lab6DLL\\Containers.h"	

// явное
void* MyAlloc(size_t siz)
{
	return malloc(siz);
}
void MyDealloc(void* ptr)
{
	return free(ptr);
}

int main()
{
	HINSTANCE ee = LoadLibraryA("lab6DLL");
	if (ee)
	{
		AssociativeArray* (*new_AssociativeArray)(Allocator, Deallocator) = GetProcAddress(ee, "new_AssociativeArray");
		void (*del_AssociativeArray)(AssociativeArray*) = GetProcAddress(ee, "del_AssociativeArray");
		void (*addKeyValue_AssociativeArray)(void*, size_t, void*, size_t, AssociativeArray*) = GetProcAddress(ee, "addKeyValue_AssociativeArray");
		Pair* (*at_AssociativeArray)(void*, size_t, AssociativeArray*) = GetProcAddress(ee, "at_AssociativeArray");

		void (*del_LinkedList)(LinkedList*) = GetProcAddress(ee, "del_LinkedList");

		printf("%p %s\n", new_AssociativeArray, "new_AssociativeArray");
		printf("%p %s\n", del_AssociativeArray, "del_AssociativeArray");
		printf("%p %s\n", addKeyValue_AssociativeArray, "addKeyValue_AssociativeArray");
		printf("%p %s\n", at_AssociativeArray, "at_AssociativeArray");

		AssociativeArray* arr = new_AssociativeArray(MyAlloc, MyDealloc);
		printf("AssociativeArray: %p\n", arr);

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
		
		FreeLibrary(ee);
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"