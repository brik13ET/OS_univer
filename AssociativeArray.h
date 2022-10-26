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

AssociativeArray* new_AssociativeArray();
void addPair_AssociativeArray(Pair, AssociativeArray*);
void addKeyValue_AssociativeArray(void* key, size_t key_size, void* value, size_t value_size, AssociativeArray*);
size_t len_AssociativeArray(AssociativeArray* a);
Pair* at_AssociativeArray(void* key, size_t key_size, AssociativeArray*);
void remove_AssociativeArray(void* key, size_t key_size, AssociativeArray*);
void del_AssociativeArray(AssociativeArray*);