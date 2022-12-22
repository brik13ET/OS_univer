#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "..\\Lab6DLL\Containers.h"
#include "..\\Lab6DLL\FileIO.h"

#define THREADCOUNT 5
#define DEBUG

HANDLE mutex;

DWORD WINAPI Thread1(LPVOID lpParam)
{
	HANDLE pool[THREADCOUNT];
	STARTUPINFO SI[THREADCOUNT];
	PROCESS_INFORMATION PI[THREADCOUNT];

	WaitForSingleObject(mutex, INFINITE);
	char buf[20];
	for (size_t i = 0; i < THREADCOUNT; i++)
	{
		int key = i;
		int val = i * i;

		ZeroMemory(&PI[i], sizeof(PI[i]));
		sprintf_s(buf, 20, "%d %d", key, val);
		ZeroMemory(&SI[i], sizeof(SI[i]));
		SI[i].cb = sizeof(SI[i]);

		CreateProcessA(
			"Lab8.exe",
			&buf,
			NULL,
			NULL,
			TRUE,
			SYNCHRONIZE,
			NULL,
			NULL,
			&SI[i],
			&PI[i]
		);
	}
	ReleaseMutex(mutex);

	for (size_t i = 0; i < THREADCOUNT; i++)
	{
		WaitForSingleObject(PI[i].hThread, INFINITE);
		CloseHandle(PI[i].hThread);
		WaitForSingleObject(PI[i].hProcess, INFINITE);
		CloseHandle(PI[i].hProcess);
	}

	ExitThread(0);
	return 0;
}

void* alloc(size_t siz)
{
	return malloc(siz);
}

void dealloc(void* ptr)
{
	free(ptr);
}


void main(void)
{
	mutex = CreateMutexW(NULL, FALSE, TEXT("GLOBAL\\mutex"));
	DWORD ids[THREADCOUNT];
	AssociativeArray* arr = new_AssociativeArray(alloc, dealloc);

	DWORD dwThreadId;
	HANDLE t1 = CreateThread(NULL, 0, Thread1, &ids[0], 0, &dwThreadId);

	WaitForSingleObject(t1, INFINITE);
	CloseHandle(t1);
	CloseHandle(mutex);

	del_AssociativeArray(arr);

	AssociativeArray* local_array = new_AssociativeArray(alloc, dealloc);
	HANDLE fd = file_open("arr.bin", FMODE_READ, OPEN_ALWAYS);
	restorebin_AssociativeArray(fd, local_array);
	file_close(fd);

	LinkedListNode* n = local_array->l->head->next;
	while (n != local_array->l->head)
	{
		Pair* p = n->data;
		printf("key: %ld\tvalue: %ld\n", *((size_t*)p->key_ptr), *((size_t*)p->value_ptr));
		n = n->next;
	}

	del_AssociativeArray(local_array);
}