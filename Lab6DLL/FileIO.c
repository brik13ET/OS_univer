#include <Windows.h>
#include "pch.h"
#include "FileIO.h"

HANDLE	file_open(char* path, enum FMODE mode, DWORD conv)
{
	DWORD access = 0;
	if (mode & FMODE_READ)
		access |= GENERIC_READ;
	if (mode & FMODE_WRITE)
		access |= GENERIC_WRITE;
	//if (mode & FMODE_APPEND)
	//	access |= GENERIC_WRITE;
	HANDLE fd = CreateFileA(path, access, 0, NULL, conv, FILE_ATTRIBUTE_NORMAL, NULL);
	return fd;
}

void	file_close(HANDLE fd)
{
	CloseHandle(fd);
}

size_t	file_read(HANDLE fd, void* buf, size_t buff_size)
{
	size_t ret = 0;
	ReadFile(fd, buf, buff_size, &ret, NULL);
	return ret;
}

size_t	file_write(HANDLE fd, void* buf, size_t buff_size)
{
	size_t ret = 0;
	WriteFile(fd, buf, buff_size, &ret, NULL);
	return ret;
}

size_t	file_pos(HANDLE fd, UINT64 offset, enum FPOS dir)
{
	size_t ret;
	SetFilePointerEx(fd, (LARGE_INTEGER) { .QuadPart = offset }, &ret, dir);
	return ret;
}

BOOL	file_iseof(HANDLE fd)
{
	size_t tmp = file_pos(fd, 0, FPOS_ADD);
	size_t end = file_pos(fd, 0, FPOS_END);
	file_pos(fd, tmp, FPOS_BEGIN);
	return tmp == end;
}