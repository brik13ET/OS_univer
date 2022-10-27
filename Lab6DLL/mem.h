#pragma once
#include <Windows.h>


typedef void* (*Allocator)(size_t);
typedef void (*Deallocator)(void*);

int MyMemcpy(void*, void*, size_t);
int MyMemcmp(void*, void*, size_t);