#pragma once
#include <stdint.h>
#include <Windows.h>
#include "mem.h"

struct LinkedListNode_s;
struct LinkedList_s;

struct LinkedList_s
{
	struct LinkedListNode_s* head;
	Allocator a;
	Deallocator d;
};

struct LinkedListNode_s
{
	void* data;
	size_t data_size;
	struct LinkedListNode_s *next;
	struct LinkedListNode_s *prev;
};

typedef struct LinkedList_s LinkedList;
typedef struct LinkedListNode_s LinkedListNode;


_CONTAINER_API LinkedList*	new_LinkedList	(Allocator, Deallocator);
_CONTAINER_API void	append_Linkedlist	(LinkedList*, void*, size_t, LinkedList*);
_CONTAINER_API void	removeAfter_Linkedlist	(LinkedListNode*, LinkedList*);
_CONTAINER_API void	removeBefore_Linkedlist(LinkedListNode*, LinkedList*);
_CONTAINER_API void	remove_LinkedList(LinkedListNode*, LinkedList*);
_CONTAINER_API void	addAfter_Linkedlist	(LinkedListNode*, void*, size_t, LinkedList*);
_CONTAINER_API void	addBefore_Linkedlist(LinkedListNode*, void*, size_t, LinkedList*);
_CONTAINER_API void	clear_Linkedlist	(LinkedList*);
_CONTAINER_API size_t	len_LinkedList		(LinkedList*);
_CONTAINER_API void	del_LinkedList(LinkedList*);
_CONTAINER_API void	savebin_LinkedList(HANDLE, LinkedList*);
_CONTAINER_API void	restorebin_LinkedList(HANDLE, LinkedList*);