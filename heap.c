#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "heap.h"
#include "common.h"

#define INT_COMP(a, b) (a - b)

HEAP_DEFINITIONS(int, int_min, INT_COMP)

int main() {
	int A[10];
	struct heap_int_min h;
	heap_int_min_create(&h, A, 10);
	assert_eq(!!h.A, 1);
	assert_eq(h.size, 0);
	assert_eq(h.cap, 10);

	heap_int_min_insert(&h, 16);
	assert_eq(heap_int_min_peek(&h), 16);
	heap_int_min_insert(&h, 8);
	heap_int_min_insert(&h, 4);
	heap_int_min_insert(&h, 2);
	heap_int_min_insert(&h, 1);
	heap_int_min_insert(&h, 0);
	assert_eq(heap_int_min_peek(&h), 0);
	assert_eq(heap_int_min_pop(&h), 0);
	assert_eq(heap_int_min_pop(&h), 1);
	assert_eq(heap_int_min_pop(&h), 2);
	assert_eq(heap_int_min_pop(&h), 4);
	assert_eq(heap_int_min_pop(&h), 8);
	assert_eq(heap_int_min_pop(&h), 16);

	heap_int_min_destroy(&h);
	assert_eq(!!h.A, 0);
	assert_eq(h.size, 0);
	assert_eq(h.cap, 0);
	return 0;
}

