#include <stdio.h>
#include <assert.h>

#include "common.h"
#include "queue.h"

QUEUE_DEFINITIONS(int, int)

struct lol {
	int val;
};

QUEUE_DEFINITIONS(struct lol, lol)

void test_lol() {
	int i;
	struct queue_lol q;
	struct lol A[10];
	queue_lol_init(&q, A, 10);
	assert_eq(q.Q == A, 1);
	assert_eq(q.cap, 10);
	assert_eq(q.siz, 0);
	assert_eq(q.fst, 0);
	assert_eq(q.lst, 0);
	for (i = 0; i < 10; ++i) {
		struct lol l;
		l.val = i;
		assert_eq(queue_lol_push(&q, l), 1);
	}
	for (i = 0; i < 10; ++i) {
		assert_eq(queue_lol_pop(&q).val, i);
	}

}

void test_int() {
	int i;
	struct queue_int q;
	int A[10];

	test_lol();

	queue_int_init(&q, A, 10);
	assert_eq(q.Q == A, 1);
	assert_eq(q.cap, 10);
	assert_eq(q.siz, 0);
	assert_eq(q.fst, 0);
	assert_eq(q.lst, 0);
	for (i = 0; i < 10; ++i) {
		assert_eq(queue_int_push(&q, i), 1);
	}
	for (i = 0; i < 10; ++i) {
		assert_eq(queue_int_pop(&q), i);
	}
}

int main() {
	test_int();
	test_lol();
	return 0;
}
