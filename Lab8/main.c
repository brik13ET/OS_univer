#include <stdlib.h>
#include <stdio.h>
#include "..\\Lab6DLL\\Containers.h"
#include "..\\Lab6DLL\\FileIO.h"

void* alloc(size_t siz)
{
	return malloc(siz);
}

void dealloc(void* ptr)
{
	free(ptr);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		return -1;
	}

	size_t k, v;
	sscanf_s(argv[0], "%ld", &k);
	sscanf_s(argv[1], "%ld", &v);

	HANDLE mutex = OpenMutexW(0, FALSE, TEXT("GLOBAL\\mutex"));
	WaitForSingleObject(mutex, INFINITE);

	AssociativeArray* arr = new_AssociativeArray(alloc, dealloc);
	HANDLE fd = file_open("arr.bin", FMODE_READ, 0);
	restorebin_AssociativeArray(fd, arr);
	file_close(fd);

	addKeyValue_AssociativeArray(&k, sizeof(k), &v, sizeof(v), arr);

	fd = file_open("arr.bin", FMODE_WRITE, 0);
	savebin_AssociativeArray(fd, arr);
	file_close(fd);

	ReleaseMutex(mutex);
	return 0;
}