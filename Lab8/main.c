#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "FileIO.h"
#include "AssociativeArray.h"

#define THREADCOUNT 5
#define DEBUG

volatile AssociativeArray* array;
volatile INT64 arg_key;
volatile INT64 arg_value;

volatile HANDLE mArray;
volatile HANDLE mArg;

DWORD WINAPI Thread2(LPVOID lpParam)
{
	WaitForSingleObject(mArray, INFINITE);
	WaitForSingleObject(mArg, INFINITE);

	addKeyValue_AssociativeArray(&arg_key, sizeof(arg_key), &arg_value, sizeof(arg_value), array);

	char tmp[20];
	sprintf_s(tmp, 20, "%u.bin", GetCurrentThreadId());
	HANDLE fd = file_open(tmp, FMODE_WRITE, CREATE_ALWAYS);
	savebin_AssociativeArray(fd, array);
	file_close(fd);

	ReleaseMutex(mArg);
	ReleaseMutex(mArray);
	Sleep(5000);
	ExitThread(0);
	return 0;
}

DWORD WINAPI Thread1(LPVOID lpParam)
{
	HANDLE pool[THREADCOUNT];
	STARTUPINFO SI[THREADCOUNT];
	PROCESS_INFORMATION PI[THREADCOUNT];
	char buf[20];
	for (size_t i = 0; i < THREADCOUNT; i++)
	{
		WaitForSingleObject(mArg, INFINITE);
		arg_key = i*i;
		arg_value = i;
		ReleaseMutex(mArg);

		ZeroMemory(&PI[i], sizeof(PI[i]));
		PI[i].hProcess = &pool[i];
		PI[i].hThread = CreateThread(NULL, 0, Thread2, NULL, 0, &((DWORD*)lpParam)[i]);
		//PI[i].dwThreadId = ((DWORD*)lpParam)[i];
		sprintf_s(buf, 20, "%d.bin", ((DWORD*)lpParam)[i]);
		ZeroMemory(&SI[i], sizeof(SI[i]));
		SI[i].cb = sizeof(SI[i]);
		SI[i].lpTitle = buf;
		//pool[i] = CreateThread(NULL, 0, Thread2, NULL, 0, &((DWORD*)lpParam)[i]);
		CreateProcessA(
			NULL,
			NULL,
			NULL,
			NULL,
			TRUE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&SI[i],
			&PI[i]
		);
		WaitForSingleObject(PI[i].hProcess, INFINITE);
		WaitForSingleObject(PI[i].hThread, INFINITE);
		
		//CloseHandle(PI[i].hProcess);
		//CloseHandle(PI[i].hThread);
	}
	WaitForSingleObject(mArray, INFINITE);
	ExitThread(0);
	return 0;
}

void main(void)
{
	mArray = CreateMutexW(NULL, FALSE, TEXT("ARRAY\0"));
	mArg = CreateMutexW(NULL, FALSE, TEXT("ARG\0"));
	DWORD ids[THREADCOUNT];
	array = new_AssociativeArray();

#ifdef DEBUG
{
	printf("\nFresh\n");
	LinkedListNode* n = array->l->head->next;
	while (n != array->l->head)
	{
		Pair* p = n->data;
		printf("key: %ld\tvalue: %ld\n", *((size_t*)p->key_ptr), *((size_t*)p->value_ptr));
	}
}
#endif // DEBUG


	DWORD dwThreadId;
	HANDLE t1 = CreateThread(NULL, 0, Thread1, &ids[0], 0, &dwThreadId);

	HANDLE OBJS[] = {mArray, mArg, t1};
	WaitForMultipleObjects(3, &OBJS[0], TRUE, INFINITE);
	CloseHandle(t1);
	CloseHandle(mArray);
	CloseHandle(mArg);

#ifdef DEBUG
	{
		printf("\nModded\n");
		LinkedListNode* n = array->l->head->next;
		while (n != array->l->head)
		{
			Pair* p = n->data;
			printf("key: %ld\tvalue: %ld\n", *((size_t*)p->key_ptr), *((size_t*)p->value_ptr));
			n= n->next;
		}
	}
#endif // DEBUG

	del_AssociativeArray(array);

	
	for (size_t i = 0; i < THREADCOUNT; i++)
	{
		AssociativeArray* local_array = new_AssociativeArray();
		char tmp[20];
		sprintf_s(tmp, 20, "%u.bin", ids[i]);
		HANDLE fd = file_open(tmp, FMODE_READ, OPEN_ALWAYS);
		restorebin_AssociativeArray(fd, local_array);
		file_close(fd);
#ifdef DEBUG
		{
			printf("\nfile \"%s\"\n", tmp);
			LinkedListNode* n = local_array->l->head->next;
			while (n != local_array->l->head)
			{
				Pair* p = n->data;
				printf("key: %ld\tvalue: %ld\n", *((size_t*)p->key_ptr), *((size_t*)p->value_ptr));
				n = n->next;
			}
		}
#endif // DEBUG
		del_AssociativeArray(local_array);
	}
}