#pragma once
#include <stdint.h>
#include <windef.h>

struct LinkedListNode_s;
struct LinkedList_s;

struct LinkedList_s
{
	struct LinkedListNode_s* head;
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


LinkedList*	new_LinkedList	();
void	append_Linkedlist	(LinkedList*, void*, size_t);
void	removeAfter_Linkedlist	(LinkedListNode*);
void	removeBefore_Linkedlist(LinkedListNode*);
void	remove_LinkedList(LinkedListNode*);
void	addAfter_Linkedlist	(LinkedListNode*, void*, size_t);
void	addBefore_Linkedlist(LinkedListNode*, void*, size_t);
void	clear_Linkedlist	(LinkedList*);
size_t	len_LinkedList		(LinkedList*);
void	del_LinkedList(LinkedList*);
void savebin_LinkedList(HANDLE, LinkedList*);
void restorebin_LinkedList(HANDLE, LinkedList*);