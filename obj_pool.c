#include <stddef.h>
#include <assert.h>
#include "obj_pool.h"

void initObjPool(ObjPool* p)
{
	p->vacancy = (1ULL << OBJ_POOL_COUNT) - 1;
}

PoolType* check_out(ObjPool* p)
{
	assert(p);
// if there can be concurrent accesses to the same pool, this needs to be done atomically
	if(!p->vacancy)
		return NULL;
	int ret_idx = __builtin_clzll(p->vacancy);
	p->vacancy &= ~(1ULL << ret_idx);
//	p->vacancy ^= 1ULL << ret_idx;	//probably more efficient but is just asking for the bit to be toggled twice in some weird race condition
// end atomic region
	return p->items + ret_idx;
}

void check_in(ObjPool* p, PoolType* x)
{	// p exists and *x is in bounds for p->items
	assert(p);
	ptrdiff_t idx = x - p->items;
	assert(idx > 0 && idx < OBJ_POOL_COUNT);

	p->vacancy |= 1ULL << idx;	// mark vacant
}