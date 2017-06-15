#include "utils.h"

void* xmalloc(Size size) {
	void *ret = malloc(size);
	return ret;
}
