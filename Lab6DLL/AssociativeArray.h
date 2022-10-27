#pragma once
#include "LinkedList.h"

struct Pair_s;
struct AssociativeArray_s;

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

typedef struct AssociativeArray_s AssociativeArray;
typedef struct Pair_s Pair;

_CONTAINER_API AssociativeArray* new_AssociativeArray();
_CONTAINER_API void addPair_AssociativeArray(Pair, AssociativeArray*);
_CONTAINER_API void addKeyValue_AssociativeArray(void* key, size_t key_size, void* value, size_t value_size, AssociativeArray*);
_CONTAINER_API size_t len_AssociativeArray(AssociativeArray* a);
_CONTAINER_API Pair* at_AssociativeArray(void* key, size_t key_size, AssociativeArray*);
_CONTAINER_API void remove_AssociativeArray(void* key, size_t key_size, AssociativeArray*);
_CONTAINER_API void del_AssociativeArray(AssociativeArray*);
_CONTAINER_API void savebin_AssociativeArray(HANDLE, AssociativeArray*);
_CONTAINER_API void restorebin_AssociativeArray(HANDLE, AssociativeArray*);