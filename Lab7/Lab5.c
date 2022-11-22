#include <Windows.h>
#include "AssociativeArray.h"
#include "FileIO.h"

#define Save

int main(int argc, char* argv[])
{
	AssociativeArray* a = new_AssociativeArray();
	#ifdef Save
	for (size_t i = 0; i <= 32; i++)
	{
		uint32_t pow3 = i*i*i;
		addKeyValue_AssociativeArray(&i, sizeof(i), &pow3, sizeof(pow3), a);
	}
	HANDLE fd = file_open("D:\\bin_test.bin", FMODE_WRITE | FMODE_READ, CREATE_ALWAYS);
	savebin_AssociativeArray(fd, a);
	#else
	HANDLE fd = file_open("D:\\bin_test.bin", FMODE_READ, OPEN_ALWAYS);
	restorebin_AssociativeArray(fd,a);
	LinkedListNode* n = a->l->head->next;
	while (n != a->l->head)
	{
		Pair* p = n->data;
		if (p)
			printf("k: %02lli\tv: %06u\t%p\n", *((size_t*)p->key_ptr), *((int*)p->value_ptr), p);
		else
			printf("%p\n", p);
		n = n->next;
	}
	#endif
	file_close(fd);
	return 0;
}