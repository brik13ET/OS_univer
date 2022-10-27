#include <stdio.h>
#include <Windows.h>
#include "..\\Lab6DLL\Containers.h"	

int main()
{
	HINSTANCE ee = LoadLibraryA("lab6DLL");
	if (ee)
	{
		AssociativeArray* (*new_AssociativeArray)() = GetProcAddress(ee, "new_AssociativeArray");
		void (*del_AssociativeArray)(AssociativeArray*) = GetProcAddress(ee, "del_AssociativeArray");
		LinkedList* (*new_LinkedList)() = GetProcAddress(ee, "new_LinkedList");
		void (*del_LinkedList)(LinkedList*) = GetProcAddress(ee, "del_LinkedList");
		printf("%p %s\n", new_AssociativeArray, "new_AssociativeArray");
		printf("%p %s\n", del_AssociativeArray, "del_AssociativeArray");
		printf("%p %s\n", new_LinkedList, "new_LinkedList");
		printf("%p %s\n", del_LinkedList, "del_LinkedList");
		LinkedList* a = new_LinkedList();
		printf("%p\n", a);
		del_LinkedList(a);
		FreeLibrary(ee);
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"