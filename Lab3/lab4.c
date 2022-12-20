#include <stdio.h>
#include "LinkedList.h"
#include "AssociativeArray.h"

#define NODE_ITERATE

int main(int argc, char* argv[])
{
	AssociativeArray* l = new_AssociativeArray();
	for (size_t i = 0; i < 10; i++)
	{
		int sq = i * i;
		addKeyValue_AssociativeArray(&i, sizeof(i), &sq, sizeof(sq), l);
	}
#ifdef NODE_ITERATE
	LinkedListNode* n = l->l->head->next;
	while (n != l->l->head)
	{
		Pair* p = n->data;
		if (p)
			printf("k: %02lli\tv: %04u\t%p\n", *((size_t*)p->key_ptr), *((int*)p->value_ptr), p);
		else
			printf("%p\n", p);
		n = n->next;
	}
#else
	size_t len = len_AssociativeArray(l);
	printf("len with head: %llu\n", len);
	for (size_t i = 0; i < len - 1; i++)
	{
		Pair* p2 = at_AssociativeArray(&i, sizeof(i), l);
		if (p2)
			printf("%02llu\tk: %02llu\tv: %04u\t%p\n", i, *((size_t*)p2->key_ptr), *((int*)p2->value_ptr), p2);
		else
			printf("%02lld\tNULL\n", i);
	}
#endif
	return 0;
}