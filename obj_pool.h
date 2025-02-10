#ifndef OBJ_POOL_H
#define OBJ_POOL_H

// OBJ_POOL_COUNT may be at most 64,
#define OBJ_POOL_COUNT	64
// if you change it to 32 or less, consider changing the type of vacancy,
// the __builtin_clzll() call, and the literal value types

typedef int PoolType;

typedef struct _ObjPool
{
	PoolType items[OBJ_POOL_COUNT];
	unsigned long long vacancy;
} ObjPool;

void initObjPool(ObjPool* p);
PoolType* check_out(ObjPool* p);
void check_in(ObjPool* p, PoolType* x);

#endif//OBJ_POOL_H