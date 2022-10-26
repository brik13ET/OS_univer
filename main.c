#include "AssociativeArray.h"
#include <locale.h>
#include <stdio.h>
#include <stdint.h>
/*
void* MyAlloc(size_t siz)
{
	HANDLE h = GetProcessHeap();
	return (void*)HeapAlloc(h, 0, siz);
}

BOOL MyFree(void* ptr)
{
	return HeapFree(GetProcessHeap(), 0, (LPVOID)ptr);
}

int* iterate(int m, int* cnt)
{
	int num_cnt = 0;
	for (size_t i = 100; i < 1000; i++)
		if ((i % 10) + (i % 100 / 10) + (i / 100) == m)
			num_cnt++;

	cnt[0] = num_cnt;
	int* ret = MyAlloc(sizeof(int)*num_cnt);
	int arr_i = 0;
	for (size_t i = 100; i < 1000; i++)
		if ((i % 10) + (i % 100 / 10) + (i / 100) == m)
		{
			ret[arr_i] = (int)i;
			arr_i++;
		}
	return ret;
}

int main(void)
{
	setlocale(LC_ALL, "ru");
	int M, count;
	scanf_s("%d", &M);
	int* arr = iterate(M, &count);
	for (int i = 0; i < count; i++)
	{
		if (i % 14 == 0)
			printf("\n");
		printf("%03d\t", arr[i]);
	}
	printf("\nВсего %d чисел\n", count);
	MyFree(arr);
}
*/
/*
int main(int argc, char* argv[])
{
	LinkedList* l = new_LinkedList();
	for (size_t i = 0; i < 32; i++)
	{
		int sq = i * i;
		append_Linkedlist(l, &sq, sizeof(sq));
	}
	LinkedListNode* n = l->head->next;
	while (n != l->head)
	{
		printf("%d\t", ((int*)n->data)[0]);
		n = n->next;
	}
	return 0;
}
*/