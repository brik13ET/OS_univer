#include "mem.h"
#include <string.h>
#include "pch.h"
#include "AssociativeArray.h"

uint8_t byte_cmp(void* p1, void* p2, size_t s, size_t ss)
{
	uint8_t ret = s == ss;
	while (ret && (s >= 0))
	{
		s--;
		ret = (((uint8_t*)p1)[s] == ((uint8_t*)p2)[s]);
	}
	return ret;
}

AssociativeArray* new_AssociativeArray(Allocator a, Deallocator d)
{
	AssociativeArray* ret = a(sizeof(AssociativeArray));
	if (ret)
	{
		ret->l = new_LinkedList(a, d);
		ret->a = a;
		ret->d = d;
	}
	return ret;
}

void addPair_AssociativeArray(Pair p, AssociativeArray* a)
{
	void
		* dup_key = a->a(p.key_size),
		* dup_val = a->a(p.value_size);
	memcpy(dup_key, p.key_ptr, p.key_size);
	memcpy(dup_val, p.value_ptr, p.value_size);	
	append_Linkedlist(a->l, &p, sizeof(p),a->l);
}

void addKeyValue_AssociativeArray(void* key, size_t key_size, void* value, size_t value_size, AssociativeArray* a)
{
	// copy key and data
	void
		* dup_key = a->a(key_size),
		* dup_val = a->a(value_size);
	if (!dup_key || !dup_val)
		return;
	memcpy(dup_key, key, key_size);
	memcpy(dup_val, value, value_size);
	Pair p = (Pair){ .key_ptr = dup_key, .key_size = key_size, .value_ptr = dup_val, .value_size = value_size };
	append_Linkedlist(a->l, &p, sizeof(Pair),a->l);
}

Pair* at_AssociativeArray(void* key_ptr, size_t key_size, AssociativeArray* a)
{
	LinkedListNode* n = a->l->head->next;
	while (
		n != a->l->head &&
		((Pair*)n->data)->key_size == key_size &&
		memcmp(((Pair*)n->data)->key_ptr, key_ptr, key_size) )
	{
		n = n->next;
	}
	if (n != a->l->head)
		return n->data;
	else
		return NULL;

}

size_t len_AssociativeArray(AssociativeArray* a)
{
	return len_LinkedList(a->l);
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
	remove_LinkedList(n, a->l);
}

void del_AssociativeArray(AssociativeArray* a)
{
	del_LinkedList(a->l);
	a->d(a);
}

void savebin_AssociativeArray(HANDLE fd, AssociativeArray* a)
{
	LinkedListNode* n = a->l->head->next;
	while (n != a->l->head)
	{
		Pair* p = n->data;
		file_write(fd, &p->key_size,	sizeof(p->key_size));
		file_write(fd, p->key_ptr,		p->key_size);
		file_write(fd, &p->value_size,	sizeof(p->value_size));
		file_write(fd, p->value_ptr,	p->value_size);
		n = n->next;
	}
}
void restorebin_AssociativeArray(HANDLE fd, AssociativeArray* a)
{
	while (!file_iseof(fd))
	{
		Pair* p = a->a(sizeof(Pair));
		file_read(fd, &p->key_size, sizeof(p->key_size));
		p->key_ptr = a->a(p->key_size);
		file_read(fd, p->key_ptr, p->key_size);
		file_read(fd, &p->value_size, sizeof(p->value_size));
		p->value_ptr = a->a(p->value_size);
		file_read(fd, p->value_ptr, p->value_size);
		addKeyValue_AssociativeArray(p->key_ptr, p->key_size, p->value_ptr, p->value_size, a);
		a->d(p->key_ptr);
		a->d(p->value_ptr);
		a->d(p);
	}
}