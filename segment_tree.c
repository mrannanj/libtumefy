#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#include "common.h"
#include "segment_tree.h"

struct st_nmax {
	int add;
	int max;
};

struct st_nmax identity_max = { 0, INT_MIN };

#define MERGE_MAX(root, left, right) do { \
	root.max = MAX(left.max, right.max); \
	root.add = 0; \
} while(0)

#define SPLIT_MAX(root, left, right) do { \
	left.add += root.add; \
	left.max += root.add; \
	right.add += root.add; \
	right.max += root.add; \
	root.add = 0; \
} while(0)

#define UPDATE_MAX(n, val) do { \
	n.max += val; \
	n.add += val; \
} while(0)

#define PRINT_MAX(n) do { \
	printf("(%d, %d) ", n.max, n.add); \
} while(0)

ST_DEFINITIONS(st_nmax, max, SPLIT_MAX, MERGE_MAX, UPDATE_MAX,
		identity_max, PRINT_MAX)

struct st_nmin {
	int add;
	int min;
};

struct st_nmin identity_min = { 0, INT_MAX };

#define MERGE_MIN(root, left, right) do { \
	root.min = MIN(left.min, right.min); \
	root.add = 0; \
} while(0)

#define SPLIT_MIN(root, left, right) do { \
	left.add += root.add; \
	left.min += root.add; \
	right.add += root.add; \
	right.min += root.add; \
	root.add = 0; \
} while(0)

#define UPDATE_MIN(n, val) do { \
	n.min += val; \
	n.add += val; \
} while(0)

#define PRINT_MIN(n) do { \
	printf("(%d, %d) ", n.min, n.add); \
} while(0)

ST_DEFINITIONS(st_nmin, min, SPLIT_MIN, MERGE_MIN, UPDATE_MIN,
		identity_min, PRINT_MIN)

void test_max() {
	int i, x;
	struct st_nmax A[64];
	struct st_max st;
	st_max_init(&st, 32, A);
	assert_eq(st.size, 32);
	assert_eq(st.tree == A, 1);
	st_max_update(&st, 0, 16, -1e9);
	assert_eq(st_max_query(&st, 0, 16).max, -1e9);

	st_max_update(&st, 1, 2, 1e9);
	st_max_update(&st, 2, 16, 2);
	assert_eq(st_max_query(&st, 0, 16).max, 0);

	assert_eq(st_max_query(&st, 0, 1).max, -1e9);
	assert_eq(st_max_query(&st, 1, 2).max, 0);
	assert_eq(st_max_query(&st, 2, 3).max, (-1e9)+2);
	assert_eq(st_max_query(&st, 3, 4).max, (-1e9)+2);
	assert_eq(st_max_query(&st, 4, 5).max, (-1e9)+2);
	assert_eq(st_max_query(&st, 6, 7).max, (-1e9)+2);

	st_max_update(&st, 0, 1, 1e9);
	st_max_update(&st, 1, 16, 1);
	assert_eq(st_max_query(&st, 0, 16).max, 1);

	x = st_max_query(&st, 3, 4).max;
	st_max_update(&st, 3, 4, -x + 6 -4);
	assert_eq(st_max_query(&st, 3, 4).max, 2);
	st_max_update(&st, 4, 16, 3);
	assert_eq(st_max_query(&st, 0, 16).max, 2);

	x = st_max_query(&st, 4, 5).max;
	st_max_update(&st, 4, 5, -x + 8 -10);
	assert_eq(st_max_query(&st, 0, 16).max, 2);

	x = st_max_query(&st, 2, 3).max;
	st_max_update(&st, 2, 3, -x + 4-1);
	assert_eq(st_max_query(&st, 0, 16).max, 3);
}

void test_min() {
	int i;
	struct st_nmin A[64];
	struct st_min st;
	st_min_init(&st, 32, A);
	assert_eq(st.size, 32);
	assert_eq(st.tree == A, 1);
	assert_eq(st.tree[1].min, 0);
	for (i = 1; i <= 15; ++i) {
		st_min_update(&st, 0, i, 1);
		assert_eq(st_min_query(&st, 0, 16).min, 0);
	}

	st_min_init(&st, 32, A);
	st_min_update(&st, 0, 10, 1);
	st_min_update(&st, 5, 10, 3);
	assert_eq(st_min_query(&st, 0, 16).min, 0);
}

int main() {
	test_max();
	test_min();
	return 0;
}
