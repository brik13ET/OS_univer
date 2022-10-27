#pragma once
#include <Windows.h>

void* MyAlloc(size_t siz);

BOOL MyFree(void* ptr);

int MyMemcpy(void*, void*, size_t);
int MyMemcmp(void*, void*, size_t);