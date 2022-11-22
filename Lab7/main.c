#include <stdio.h>
#include "AssociativeArray.h"
#include "FileIO.h"

#define THREADCOUNT 5

AssociativeArray* arr;
int newNumber = 0;

HANDLE hThread1;
HANDLE hThread2;
HANDLE hMutex[2];

WORD WINAPI Thread2(CONST LPVOID lpParam) {

	
	//while (WaitForSingleObject(hMutex[0], INFINITE) != WAIT_OBJECT_0);
	////OpenMutexW(hMutex[0], FALSE, NULL);
	//int sq = newNumber * newNumber;
	//int i = newNumber;
	//if (!ReleaseMutex(hMutex[0]))
	//	ExitThread(GetCurrentThreadId());

	int i = GetCurrentThreadId();
	int sq = i * i;
	char f[20];

	while (WaitForSingleObject(hMutex[1], INFINITE) != WAIT_OBJECT_0);
	
	addKeyValue_AssociativeArray(&i, sizeof(i), &sq, sizeof(sq), arr);

	if (!ReleaseMutex(hMutex[1]))
		ExitThread(GetCurrentThreadId());
	
	sprintf(&f[0], "%0.10d.bin", GetCurrentThreadId());
	HANDLE fd = file_open(&f[0], FMODE_WRITE, NULL);
	savebin_AssociativeArray(fd, arr);
	file_close(fd);
	
	ReleaseMutex(hMutex[1]);
	
	ExitThread(0);
	return 0;
}

WORD WINAPI Thread1(CONST LPVOID lpParam) {
	UNREFERENCED_PARAMETER(lpParam);
	HANDLE aThread[THREADCOUNT];
	for (size_t i = 0; i < THREADCOUNT; i++)
	{
		while(WaitForSingleObject(hMutex[0], INFINITE) != WAIT_OBJECT_0);
		newNumber = i;
		if (!ReleaseMutex(hMutex[0]))
			return GetCurrentThreadId();

		aThread[i] = CreateThread(NULL, 0, &Thread2, &newNumber, 0, NULL);
	}
	WaitForMultipleObjects(THREADCOUNT, &aThread[0], TRUE, INFINITE);
	for (size_t i = 0; i < THREADCOUNT; i++)
		CloseHandle(aThread[i]);
	ExitThread(0);
	return 0;
}

int main() {
	arr = new_AssociativeArray();
	hMutex[0] = CreateMutex(NULL, FALSE, NULL);
	hMutex[1] = CreateMutex(NULL, FALSE, NULL);
	if (NULL == hMutex[0] || NULL == hMutex[1]) {
		fprintf(stderr, "mutex = null");
	}
	HANDLE th1 = CreateThread(NULL, 0, Thread1, NULL, NULL, NULL);
	WaitForSingleObject(th1, INFINITE);
	WaitForMultipleObjects(2, &hMutex[0], TRUE, INFINITE);
	CloseHandle(th1);
	CloseHandle(hMutex[0]);
	CloseHandle(hMutex[1]);
	LinkedListNode* n = arr->l->head->next;
	while(n != arr->l->head)
	{
		Pair* r = (Pair*)n->data;
		if (r != NULL)
		printf("%d: \t%d\n", *((int*)r->key_ptr), *((int*)r->value_ptr));
		n = n->next;
	}
	del_AssociativeArray(arr);
	return 0;
}