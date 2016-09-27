#include "utils.h"

void* xmalloc(size_t size) {
	void *ret = malloc(size);
	return ret;
}
