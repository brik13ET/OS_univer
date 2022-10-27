#pragma once
#define CONTAINER_API __declspec(dllimport)
#include "pch.h"

struct Pair_s;
struct AssociativeArray_s;
struct LinkedListNode_s;
struct LinkedList_s;

typedef struct LinkedList_s LinkedList;
typedef struct LinkedListNode_s LinkedListNode;
typedef struct AssociativeArray_s AssociativeArray;
typedef struct Pair_s Pair;

struct LinkedList_s
{
	struct LinkedListNode_s* head;
};

struct LinkedListNode_s
{
	void* data;
	size_t data_size;
	struct LinkedListNode_s* next;
	struct LinkedListNode_s* prev;
};

struct Pair_s
{
	void* key_ptr;
	size_t key_size;
	void* value_ptr;
	size_t value_size;
};

struct AssociativeArray_s
{
	LinkedList* l;
};


CONTAINER_API HANDLE	file_open(char*, enum FMODE, DWORD);
CONTAINER_API void		file_close(HANDLE);
CONTAINER_API size_t	file_read(HANDLE, void*, size_t);
CONTAINER_API size_t	file_write(HANDLE, void*, size_t);
CONTAINER_API size_t	file_pos(HANDLE, UINT64, enum FPOS);
CONTAINER_API BOOL		file_iseof(HANDLE);

CONTAINER_API LinkedList* new_LinkedList();
CONTAINER_API void	append_Linkedlist(LinkedList*, void*, size_t);
CONTAINER_API void	removeAfter_Linkedlist(LinkedListNode*);
CONTAINER_API void	removeBefore_Linkedlist(LinkedListNode*);
CONTAINER_API void	remove_LinkedList(LinkedListNode*);
CONTAINER_API void	addAfter_Linkedlist(LinkedListNode*, void*, size_t);
CONTAINER_API void	addBefore_Linkedlist(LinkedListNode*, void*, size_t);
CONTAINER_API void	clear_Linkedlist(LinkedList*);
CONTAINER_API size_t	len_LinkedList(LinkedList*);
CONTAINER_API void	del_LinkedList(LinkedList*);
CONTAINER_API void	savebin_LinkedList(HANDLE, LinkedList*);
CONTAINER_API void	restorebin_LinkedList(HANDLE, LinkedList*);

CONTAINER_API AssociativeArray* new_AssociativeArray();
CONTAINER_API void addPair_AssociativeArray(Pair, AssociativeArray*);
CONTAINER_API void addKeyValue_AssociativeArray(void* key, size_t key_size, void* value, size_t value_size, AssociativeArray*);
CONTAINER_API size_t len_AssociativeArray(AssociativeArray* a);
CONTAINER_API Pair* at_AssociativeArray(void* key, size_t key_size, AssociativeArray*);
CONTAINER_API void remove_AssociativeArray(void* key, size_t key_size, AssociativeArray*);
CONTAINER_API void del_AssociativeArray(AssociativeArray*);
CONTAINER_API void savebin_AssociativeArray(HANDLE, AssociativeArray*);
CONTAINER_API void restorebin_AssociativeArray(HANDLE, AssociativeArray*);