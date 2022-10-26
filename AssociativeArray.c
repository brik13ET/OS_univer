#include <stdlib.h>
#include "AssociativeArray.h"

uint8_t byte_cmp(void* p1, void* p2, size_t s, size_t ss)
{
	uint8_t ret = s == ss;
	while (ret && s >= 0)
	{
		s--;
		ret = (((uint8_t*)p1)[s] == ((uint8_t*)p1)[s]);
	}
	return ret;
}

AssociativeArray* new_AssociativeArray()
{
	AssociativeArray* ret = malloc(sizeof(AssociativeArray));
	LinkedList* ll = new_LinkedList();
	ret->l->head = ll->head;
}

void addPair_AssociativeArray(Pair p, AssociativeArray* a)
{
	append_Linkedlist(a->l, &p, sizeof(p));
}

void addKeyValue_AssociativeArray(void* key, size_t key_size, void* value, size_t value_size, AssociativeArray* a)
{
	Pair p = (Pair){ .key_ptr = key, .key_size = key_size, .value_ptr = value, .value_size = value_size };
	append_Linkedlist(a->l, &p, sizeof(Pair));
}

Pair* at_AssociativeArray(void* key, size_t key_size, AssociativeArray* a)
{
	LinkedListNode* n = a->l->head->next;
	while (n != a->l->head && !byte_cmp(key, n->data, key_size, n->data_size))
	{
		n = n->next;
	}
	if (n != a->l->head)
		return n;
	else
		return NULL;

}

void remove_AssociativeArray(void* key, size_t key_size, AssociativeArray* a)
{
	LinkedListNode* n = a->l->head->next;
	while (n != a->l->head && !byte_cmp(key, n->data, key_size, n->data_size))
	{
		n = n->next;
	}
	if (n == a->l->head)
		return;
	remove_LinkedList(n);
}

void del_AssociativeArray(AssociativeArray* a)
{
	del_LinkedList(a->l);
	free(a);
}
