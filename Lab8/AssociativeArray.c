#include <stdlib.h>
#include <string.h>
#include "AssociativeArray.h"
#include "FileIO.h"

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
	if (ret)
		ret->l = new_LinkedList();
	return ret;
}

void addPair_AssociativeArray(Pair p, AssociativeArray* a)
{
	void
		* dup_key = malloc(p.key_size),
		* dup_val = malloc(p.value_size);
	if (!dup_key || !dup_val)
		return;
	memcpy(dup_key, p.key_ptr, p.key_size);
	memcpy(dup_val, p.value_ptr, p.value_size);	
	p.key_ptr = dup_key;
	p.value_ptr = dup_val;
	append_Linkedlist(a->l, &p, sizeof(p));
}

void addKeyValue_AssociativeArray(void* key, size_t key_size, void* value, size_t value_size, AssociativeArray* a)
{
	// copy key and data
	void
		* dup_key = malloc(key_size),
		* dup_val = malloc(value_size);
	if (!dup_key || !dup_val)
		return;
	memcpy(dup_key, key, key_size);
	memcpy(dup_val, value, value_size);
	Pair p = (Pair){ .key_ptr = dup_key, .key_size = key_size, .value_ptr = dup_val, .value_size = value_size };
	append_Linkedlist(a->l, &p, sizeof(Pair));
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
	remove_LinkedList(n);
}

void del_AssociativeArray(AssociativeArray* a)
{
	del_LinkedList(a->l);
	free(a);
}

void savebin_AssociativeArray(HANDLE fd, AssociativeArray* a)
{
	LinkedListNode* n = a->l->head->next;
	while (n != a->l->head)
	{
		Pair* p = n->data;
		file_write(fd, &p->key_size, sizeof(p->key_size));
		file_write(fd, p->key_ptr, p->key_size);
		file_write(fd, &p->value_size, sizeof(p->value_size));
		file_write(fd, p->value_ptr, p->value_size);
		n = n->next;
	}
}
void restorebin_AssociativeArray(HANDLE fd, AssociativeArray* a)
{
	void* buf;
	BOOL ERR_EOF;
	size_t siz;
	file_pos(fd, 0, FPOS_BEGIN);
	while (!file_iseof(fd))
	{
		Pair* p = malloc(sizeof(Pair));
		ERR_EOF = file_read(fd, &p->key_size, sizeof(p->key_size)) > 0;
		if (!ERR_EOF)
		{
			free(p);
			return;
		}
		p->key_ptr = malloc(p->key_size);
		file_read(fd, p->key_ptr, p->key_size);
		file_read(fd, &p->value_size, sizeof(p->value_size));
		p->value_ptr = malloc(p->value_size);
		file_read(fd, p->value_ptr, p->value_size);
		addKeyValue_AssociativeArray(p->key_ptr, p->key_size, p->value_ptr, p->value_size, a);
		free(p->key_ptr);
		free(p->value_ptr);
		free(p);
	}
}