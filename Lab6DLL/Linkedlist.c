#pragma once
#include <stdlib.h>
#include <string.h>
#include "pch.h"
#include "mem.h"
#include "LinkedList.h"
#include "FileIO.h"

// Cycle double linked list

LinkedList* new_LinkedList(Allocator a, Deallocator d)
{
	int siz = sizeof(LinkedList);
	LinkedList* ret = (LinkedList*)a(siz);
	if (ret)
	{
		ret->a = a;
		ret->d = d;
		ret->head = (LinkedListNode*)a(sizeof(LinkedListNode));
		ret->head->data = 0;
		ret->head->data_size = 0;
		ret->head->next = ret->head;
		ret->head->prev = ret->head;
	}
	return ret;
}

void	append_Linkedlist(LinkedList* l, void* data_ptr, size_t siz)
{
	addBefore_Linkedlist(l->head, data_ptr, siz, l);
}

void	removeAfter_Linkedlist(LinkedListNode* n, LinkedList* l)
{
	if (!n && !n->next)
		return;
	remove_LinkedList(n->next, l);

}

void	removeBefore_Linkedlist(LinkedListNode* n, LinkedList *l)
{
	if (!n && !n->prev)
		return;
	remove_LinkedList(n->prev, l);
}

void	remove_LinkedList(LinkedListNode* n, LinkedList* l)
{
	if (!n)
		return;
	n->prev->next = n->next;
	n->next->prev = n->prev;
	l->d(n->data);
	l->d(n);
}

void	addAfter_Linkedlist(LinkedListNode* n, void* data_ptr, size_t siz, LinkedList* l)
{
	if (!n)
		return;
	LinkedListNode* nn = l->a(sizeof(LinkedListNode));
	nn->data = l->a(siz);
	nn->data_size = siz;

	nn->next = n->next;
	nn->prev = n;
	n->next = nn;
	n->next->prev = nn;

	memcpy_s(nn->data, nn->data_size, data_ptr, siz);
}

void	addBefore_Linkedlist(LinkedListNode* n, void* data_ptr, size_t siz, LinkedList* l)
{
	if (!n)
		return;
	LinkedListNode* nn = l->a(sizeof(LinkedListNode));
	nn->data = l->a(siz);
	nn->data_size = siz;

	nn->next = n;
	nn->prev = n->prev;
	nn->prev->next = nn;
	n->prev = nn;

	memcpy_s(nn->data, siz, data_ptr, siz);
}

void	clear_Linkedlist(LinkedList* l)
{
	if (!l)
		return;
	LinkedListNode* n = l->head->next;
	l->head->next = l->head;
	l->head->prev = l->head;
	while (n != l->head)
	{
		l->d(n->data);
		n = n->next;
		if (n->prev != l->head)
			l->d(n->prev);
	}
}

size_t	len_LinkedList(LinkedList* l)
{
	if (!l)
		return -1;
	size_t ret = 1;
	LinkedListNode* n = l->head->next;
	while (n != l->head)
	{
		n = n->next;
		ret++;
	}
	return ret;
}

void	del_LinkedList(LinkedList* l)
{
	clear_Linkedlist(l);
	remove_LinkedList(l->head, l);
	l->d(l);
}

void savebin_LinkedList(HANDLE fd, LinkedList* l)
{
	LinkedListNode *n = l->head->next;
	while (n != l->head)
	{
		
		file_write(fd, &(n->data_size), sizeof(n->data_size));
		file_write(fd, n->data, n->data_size);
		n = n->next;
	}
}

void restorebin_LinkedList(HANDLE fd, LinkedList* l)
{
	void* buf;
	size_t siz;
	while (!file_iseof(fd))
	{
		file_read(fd, &siz, sizeof(siz));
		buf = l->a(siz);
		file_read(fd, buf, siz);
		addBefore_Linkedlist(l->head, buf, siz, l);
		l->d(buf);
	}
}
