#include <stdio.h>
#include <locale.h>

#define USENATIVE
#ifdef USENATIVE

#include <Windows.h>

void* MyAlloc(size_t siz)
{
	HANDLE h = GetProcessHeap();
	return (void*)HeapAlloc(h, 0, siz);
}

BOOL MyFree(void* ptr)
{
	return HeapFree(GetProcessHeap(), 0, (LPVOID)ptr);
}


#define ALLOC(X) MyAlloc(X)
#define FREE(X) MyFree(X)

#else

#include <stdlib.h>

#define ALLOC(X) malloc(X)
#define FREE(X) free(X)


#endif



void main(void)
{
	int arr_dim1, arr_dim2;
	setlocale(LC_ALL, "ru");
	printf("¬ведите размеры массива: ");
	scanf_s("%d %d", &arr_dim1, &arr_dim2);
	int** arr = ALLOC(sizeof(int*) * arr_dim1);
	if (!arr)
	{
		fprintf(stderr, "unable alloc() for %d bytes\n", (int)sizeof(int) * arr_dim1 * arr_dim2);
		return;
	}
	for (int i = 0; i < arr_dim1; i++)
	{
		arr[i] = ALLOC(sizeof(int) * arr_dim2);
	}

	for (size_t i = 0; i < arr_dim1; i++)
	{
		for (size_t j = 0; j < arr_dim2; j++)
		{
			arr[i][j] = i * arr_dim2 + j;
			printf("%d\t", arr[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');

	for (size_t i = 0; i < arr_dim1; i++)
	{
		float sum = 0;
		for (size_t j = 0; j < arr_dim2; j++)
			sum += arr[i][j];
		for (size_t j = 0; j < arr_dim2; j++)
			*((float*)&arr[i][j]) = arr[i][j] / sum;
		for (size_t j = 0; j < arr_dim2; j++)
			printf("%01.4lf\t", *((float*)&arr[i][j]));
		putchar('\n');
	}

	for (int i = 0; i < arr_dim1; i++)
	{
		FREE(arr[i]);
	}
	FREE(arr);
}