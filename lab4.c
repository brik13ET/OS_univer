#include <stdio.h>
#include "AssociativeArray.h"

void main(void)
{
	AssociativeArray* a = new_AssociativeArray();
	for (size_t i = 0; i < 16; i++)
	{
		int sq = i * i;
		addKeyValue_AssociativeArray(&i, sizeof(i), &sq, sizeof(sq), a);
	}
	int lenArr = len_LinkedList(a->l);
	printf("ArrayLen: %d\n", len_LinkedList(a->l));
	for (size_t i = 0; i < lenArr; i++)
	{
		Pair* p = at_AssociativeArray(&i, sizeof(i), a);
		printf("key: %d\tvalue: %d\n", ((size_t*)p->key_ptr)[0], ((int*)p->value_ptr)[0]);
	}
}
