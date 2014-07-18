#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avl_tree.h"

#define INT_COMPARE(a, b) (a - b)

AVL_DEFINITIONS(int, int, INT_COMPARE)

struct avl_int_node qn[10];
struct avl_int_node tn[10];

int main()
{
	struct avl_int_tree t;

	avl_int_init(&t, tn, 10);
	assert_eq(t.root == NULL, 1);
	assert_eq(t.free_node == tn, 1);

	/* single left rotation */
	avl_int_init(&t, tn, 10);
	assert_eq(avl_int_insert(&t, 1), 1);
	assert_eq(avl_int_insert(&t, 2), 1);
	assert_eq(avl_int_insert(&t, 3), 1);
	assert_eq(avl_int_search(&t, 1) != NULL, 1);
	assert_eq(avl_int_search(&t, 2) != NULL, 1);
	assert_eq(avl_int_search(&t, 3) != NULL, 1);
	assert_eq(AVL_BALANCE_FACTOR(t.root), 0);
	assert_eq(t.root->height, 2);

	/* single right rotation */
	avl_int_init(&t, tn, 10);
	assert_eq(avl_int_insert(&t, 3), 1);
	assert_eq(avl_int_insert(&t, 2), 1);
	assert_eq(avl_int_insert(&t, 1), 1);
	assert_eq(avl_int_search(&t, 1) != NULL, 1);
	assert_eq(avl_int_search(&t, 2) != NULL, 1);
	assert_eq(avl_int_search(&t, 3) != NULL, 1);
	assert_eq(t.root->height, 2);
	assert_eq(AVL_BALANCE_FACTOR(t.root), 0);

	/* double left rotation */
	avl_int_init(&t, tn, 10);
	assert_eq(avl_int_insert(&t, 1), 1);
	assert_eq(avl_int_insert(&t, 3), 1);
	assert_eq(avl_int_insert(&t, 2), 1);
	assert_eq(avl_int_search(&t, 1) != NULL, 1);
	assert_eq(avl_int_search(&t, 2) != NULL, 1);
	assert_eq(avl_int_search(&t, 3) != NULL, 1);
	assert_eq(t.root->height, 2);
	assert_eq(AVL_BALANCE_FACTOR(t.root), 0);

	/* double right rotation */
	avl_int_init(&t, tn, 10);
	assert_eq(avl_int_insert(&t, 3), 1);
	assert_eq(avl_int_insert(&t, 1), 1);
	assert_eq(avl_int_insert(&t, 2), 1);
	assert_eq(avl_int_search(&t, 1) != NULL, 1);
	assert_eq(avl_int_search(&t, 2) != NULL, 1);
	assert_eq(avl_int_search(&t, 3) != NULL, 1);
	assert_eq(t.root->height, 2);
	assert_eq(AVL_BALANCE_FACTOR(t.root), 0);

	/* delete */
	avl_int_init(&t, tn, 10);
	assert_eq(avl_int_insert(&t, 3), 1);
	assert_eq(avl_int_insert(&t, 1), 1);
	assert_eq(avl_int_insert(&t, 2), 1);
	assert_eq(avl_int_search(&t, 1) != NULL, 1);
	assert_eq(avl_int_search(&t, 2) != NULL, 1);
	assert_eq(avl_int_search(&t, 3) != NULL, 1);
	assert_eq(t.root->height, 2);
	assert_eq(AVL_BALANCE_FACTOR(t.root), 0);

	assert_eq(avl_int_search(&t, -10) == NULL, 1);
	assert_eq(avl_int_delete(&t, -10), 0);

	assert_eq(avl_int_search(&t, 1) != NULL, 1);
	assert_eq(avl_int_delete(&t, 1), 1);
	assert_eq(avl_int_search(&t, 1) == NULL, 1);
	assert_eq(avl_int_delete(&t, 1), 0);
	assert_eq(avl_int_delete(&t, 1), 0);

	assert_eq(avl_int_search(&t, 2) != NULL, 1);
	assert_eq(avl_int_delete(&t, 2), 1);
	assert_eq(avl_int_search(&t, 2) == NULL, 1);
	assert_eq(avl_int_delete(&t, 2), 0);
	assert_eq(avl_int_delete(&t, 2), 0);

	assert_eq(avl_int_search(&t, 3) != NULL, 1);
	assert_eq(avl_int_delete(&t, 3), 1);
	assert_eq(avl_int_search(&t, 3) == NULL, 1);
	assert_eq(avl_int_delete(&t, 3), 0);

	assert_eq(avl_int_insert(&t, 0), 1);
	assert_eq(avl_int_insert(&t, 1), 1);
	assert_eq(avl_int_insert(&t, 2), 1);
	assert_eq(avl_int_insert(&t, 3), 1);
	assert_eq(avl_int_insert(&t, 4), 1);
	assert_eq(avl_int_insert(&t, 5), 1);
	assert_eq(avl_int_insert(&t, 6), 1);
	assert_eq(avl_int_insert(&t, 7), 1);
	assert_eq(avl_int_insert(&t, 8), 1);
	assert_eq(avl_int_insert(&t, 9), 1);
	assert_eq(avl_int_insert(&t, 10), 0);
	assert_eq(avl_int_insert(&t, 0), 0);
	assert_eq(avl_int_insert(&t, 1), 0);
	assert_eq(avl_int_insert(&t, 2), 0);
	assert_eq(avl_int_insert(&t, 3), 0);
	assert_eq(avl_int_insert(&t, 4), 0);
	assert_eq(avl_int_insert(&t, 5), 0);
	assert_eq(avl_int_insert(&t, 6), 0);
	assert_eq(avl_int_insert(&t, 7), 0);
	assert_eq(avl_int_insert(&t, 8), 0);
	assert_eq(avl_int_insert(&t, 9), 0);

	assert_eq(avl_int_delete(&t, 0), 1);
	assert_eq(avl_int_delete(&t, 1), 1);
	assert_eq(avl_int_delete(&t, 2), 1);
	assert_eq(avl_int_delete(&t, 3), 1);
	assert_eq(avl_int_delete(&t, 4), 1);
	assert_eq(avl_int_delete(&t, 5), 1);
	assert_eq(avl_int_delete(&t, 6), 1);
	assert_eq(avl_int_delete(&t, 7), 1);
	assert_eq(avl_int_delete(&t, 8), 1);
	assert_eq(avl_int_delete(&t, 9), 1);

	/* TODO: add test for this */
	avl_int_print(&t, qn, 10);

	return 0;
}
