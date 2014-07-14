#pragma once

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(a,b) do { \
	char swap_tmp[sizeof(a) == sizeof(b) ? (int)sizeof(a) : -1]; \
	memcpy(swap_tmp, &a, sizeof(a)); \
	memcpy(&a, &b, sizeof(a)); \
	memcpy(&b, swap_tmp, sizeof(a)); \
} while(0)

#define HEAP_STRUCT_NAME(name) heap_##name

#define HEAP_DEF_STRUCT(type, name) \
struct HEAP_STRUCT_NAME(name) { \
	type* A; \
	int size; \
	int cap; \
};

#define HEAP_DEF_CREATE(type, name) \
void heap_##name##_create(struct HEAP_STRUCT_NAME(name)* h, \
		type* A, int cap) \
{ \
	h->A = A; \
	h->cap = cap; \
	h->size = 0; \
}

#define HEAP_DEF_DESTROY(type, name) \
void heap_##name##_destroy(struct HEAP_STRUCT_NAME(name)* h) \
{ \
	h->A = NULL; \
	h->cap = 0; \
	h->size = 0; \
}

#define HEAP_DEF_HEAPIFY(type, name, compare) \
void heap_##name##_heapify(struct HEAP_STRUCT_NAME(name)* h, int i) { \
	int l = (i<<1) + 1; \
	int r = (i<<1) + 2; \
	int smallest = i; \
	if (l < h->size && compare(h->A[l], h->A[smallest]) < 0) { \
		smallest = l; \
	} if (r < h->size && compare(h->A[r], h->A[smallest]) < 0) { \
		smallest = r; \
	} if (smallest != i) { \
		SWAP(h->A[smallest], h->A[i]); \
		heap_##name##_heapify(h, smallest); \
	} \
}

#define HEAP_DEF_POP(type, name) \
type heap_##name##_pop(struct HEAP_STRUCT_NAME(name)* h) { \
	assert(h->size > 0); \
	type ret = h->A[0]; \
	h->size--; \
	h->A[0] = h->A[h->size]; \
	heap_##name##_heapify(h, 0); \
	return ret; \
}

#define HEAP_DEF_PEEK(type, name) \
type heap_##name##_peek(struct HEAP_STRUCT_NAME(name)* h) { \
	assert(h->size > 0); \
	return h->A[0]; \
}

#define HEAP_DEF_INSERT(type, name, compare) \
void heap_##name##_insert(struct HEAP_STRUCT_NAME(name)* h, type val) { \
	int p, c; \
	assert(h->size + 1 <= h->cap); \
	c = h->size++; \
	memcpy(&h->A[c], &val, sizeof(val)); \
	for (p = c>>1; compare(h->A[c], h->A[p]) < 0; c = p, p = c>>1) { \
		SWAP(h->A[p], h->A[c]); \
	} \
}

#define HEAP_DEFINITIONS(type, name, compare) \
	HEAP_DEF_STRUCT(type, name) \
	HEAP_DEF_CREATE(type, name) \
	HEAP_DEF_DESTROY(type, name) \
	HEAP_DEF_HEAPIFY(type, name, compare) \
	HEAP_DEF_POP(type, name) \
	HEAP_DEF_PEEK(type, name) \
	HEAP_DEF_INSERT(type, name, compare)

