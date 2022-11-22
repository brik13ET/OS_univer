#pragma once

#include <Windows.h>

enum FMODE
{
	FMODE_READ =	1 << 1,
	FMODE_WRITE =	1 << 2,
	FMODE_APPEND=(1 << 2) | (1 << 3),
};

enum FPOS
{
	FPOS_BEGIN = 0,
	FPOS_ADD = 1,
	FPOS_END = 2
};

HANDLE	file_open(char*,enum FMODE, DWORD);
void	file_close(HANDLE);
size_t	file_read(HANDLE, void*, size_t);
size_t	file_write(HANDLE, void*, size_t);
size_t	file_pos(HANDLE, UINT64, enum FPOS);
BOOL	file_iseof(HANDLE);