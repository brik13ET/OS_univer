#pragma once
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

// Cycle double linked list

LinkedList* new_LinkedList()
{
	LinkedList* ret = (LinkedList*)malloc(sizeof(LinkedList));
	if (ret)
	{
		ret->head = (LinkedListNode*)malloc(sizeof(LinkedListNode));
		ret->head->data = 0;
		ret->head->data_size = 0;
		ret->head->next = ret->head;
		ret->head->prev = ret->head;
	}
	return ret;
}

void	append_Linkedlist(LinkedList* l, void* data_ptr, size_t siz)
{
	addBefore_Linkedlist(l->head, data_ptr, siz);
}

void	removeAfter_Linkedlist(LinkedListNode* n)
{
	if (!n && !n->next)
		return;
	remove_LinkedList(n->next);

}

void	removeBefore_Linkedlist(LinkedListNode* n)
{
	if (!n && !n->prev)
		return;
	remove_LinkedList(n->prev);
}

void	remove_LinkedList(LinkedListNode* n)
{
	if (!n)
		return;
	n->prev->next = n->next;
	n->next->prev = n->prev;
	free(n->data);
	free(n);
}

void	addAfter_Linkedlist(LinkedListNode* n, void* data_ptr, size_t siz)
{
	if (!n)
		return;
	LinkedListNode* nn = malloc(sizeof(LinkedListNode));
	nn->data = malloc(siz);
	nn->data_size = siz;

	nn->next = n->next;
	nn->prev = n;
	n->next = nn;
	n->next->prev = nn;

	memcpy_s(nn->data, nn->data_size, data_ptr, siz);
}

void	addBefore_Linkedlist(LinkedListNode* n, void* data_ptr, size_t siz)
{
	if (!n)
		return;
	LinkedListNode* nn = malloc(sizeof(LinkedListNode));
	nn->data = malloc(siz);
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
		free(n->data);
		n = n->next;
		if (n->prev != l->head)
			free(n->prev);
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
	remove_LinkedList(l->head);
	free(l);
}