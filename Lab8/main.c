#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "FileIO.h"
#include "AssociativeArray.h"

#define THREADCOUNT 5
#define DEBUG

typedef struct ARG
{
	Pair p;
	int64_t key;
	int64_t value;
	HANDLE mArg;
	AssociativeArray* array;
} arg;
volatile arg a1;


DWORD WINAPI Thread2(LPVOID lpParam)
{
	*(arg**)lpParam = &a1;
	//while (*(arg**)lpParam == NULL);
	WaitForSingleObject(a1.mArg, INFINITE);


	char tmp[20];

	a1.p.key_ptr = &a1.key;
	a1.p.value_ptr = &a1.value;
	a1.p.key_size = sizeof(a1.key);
	a1.p.value_size = sizeof(a1.value);

	addPair_AssociativeArray(a1.p, a1.array);

	sprintf_s(tmp, sizeof(tmp), "%u.bin", GetCurrentThreadId());
	HANDLE fd = file_open(tmp, FMODE_WRITE, CREATE_ALWAYS);
	savebin_AssociativeArray(fd, a1.array);
	file_close(fd);

	ReleaseMutex(a1.mArg);
	ExitThread(0);
	return 0;
}

DWORD WINAPI Thread1(LPVOID lpParam)
{
	HANDLE pool[THREADCOUNT];
	STARTUPINFO SI[THREADCOUNT];
	PROCESS_INFORMATION PI[THREADCOUNT];
	char buf[20];
	a1.p.key_ptr = &a1.key;
	a1.p.value_ptr = &a1.value;
	for (size_t i = 0; i < THREADCOUNT; i++)
	{
		WaitForSingleObject(a1.mArg, INFINITE);
		a1.key = i*i;
		a1.value = i;
		ReleaseMutex(a1.mArg);

		arg* t_arg = NULL;

		ZeroMemory(&PI[i], sizeof(PI[i]));
		PI[i].hProcess = &pool[i];
		PI[i].hThread = CreateThread(
			NULL,
			0,
			Thread2,
			&t_arg,
			CREATE_SUSPENDED,
			&((DWORD*)lpParam)[i]
		);
		//PI[i].dwThreadId = ((DWORD*)lpParam)[i];
		sprintf_s(buf, 20, "%d.bin", ((DWORD*)lpParam)[i]);
		ZeroMemory(&SI[i], sizeof(SI[i]));
		SI[i].cb = sizeof(SI[i]);
		SI[i].lpTitle = buf;
		SI[i].dwFlags |= PROCESS_VM_READ | PROCESS_VM_WRITE;
		
		CreateProcessA(
			NULL,
			NULL,
			NULL,
			NULL,
			TRUE,
			CREATE_NEW_CONSOLE | SYNCHRONIZE,
			NULL,
			NULL,
			&SI[i],
			&PI[i]
		);
		ResumeThread(PI[i].hThread);
		while (t_arg == NULL);
		WriteProcessMemory(PI[i].hProcess, t_arg, &a1, sizeof(a1), sizeof(a1));
		//ReadProcessMemory(PI[i].hProcess, t_arg, &a1, sizeof(a1), sizeof(a1));
	}

	for (size_t i = 0; i < THREADCOUNT; i++)
	{
		WaitForSingleObject(PI[i].hThread, INFINITE);
		CloseHandle(PI[i].hThread);
		//WaitForSingleObject(PI[i].hProcess, INFINITE);
		//CloseHandle(PI[i].hProcess);
	}

	ExitThread(0);
	return 0;
}

void main(void)
{
	a1.mArg = CreateMutexW(NULL, FALSE, TEXT("ARG\0"));
	DWORD ids[THREADCOUNT];
	a1.array = new_AssociativeArray();

#ifdef DEBUG
{
	printf("\nFresh\n");
	LinkedListNode* n = a1.array->l->head->next;
	while (n != a1.array->l->head)
	{
		Pair* p = n->data;
		printf("key: %ld\tvalue: %ld\n", *((size_t*)p->key_ptr), *((size_t*)p->value_ptr));
	}
}
#endif // DEBUG


	DWORD dwThreadId;
	HANDLE t1 = CreateThread(NULL, 0, Thread1, &ids[0], 0, &dwThreadId);

	HANDLE OBJS[] = {a1.mArg, t1};
	WaitForMultipleObjects(2, &OBJS[0], TRUE, INFINITE);
	CloseHandle(t1);
	CloseHandle(a1.mArg);

#ifdef DEBUG
	{
		printf("\nModded\n");
		LinkedListNode* n = a1.array->l->head->next;
		while (n != a1.array->l->head)
		{
			Pair* p = n->data;
			printf("key: %ld\tvalue: %ld\n", *((size_t*)p->key_ptr), *((size_t*)p->value_ptr));
			n= n->next;
		}
	}
#endif // DEBUG

	del_AssociativeArray(a1.array);

	
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