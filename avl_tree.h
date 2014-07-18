#pragma once

#include <assert.h>

#include "common.h"
#include "queue.h"

#define AVL_NODE_NAME(name) avl_##name##_node
#define AVL_TREE_NAME(name) avl_##name##_tree

#define AVL_DEF_NODE(type, name) \
struct AVL_NODE_NAME(name) { \
	struct AVL_NODE_NAME(name)* left; \
	struct AVL_NODE_NAME(name)* right; \
	int height; \
	type value; \
};

#define AVL_DEF_TREE(type, name) \
struct AVL_TREE_NAME(name) { \
	struct AVL_NODE_NAME(name)* root; \
	struct AVL_NODE_NAME(name)* free_node; \
};

#define AVL_DEF_INIT(type, name) \
void avl_##name##_init(struct AVL_TREE_NAME(name)* t, \
		struct AVL_NODE_NAME(name)* n, int size) \
{ \
	int i; \
	assert(size > 0); \
	assert(n); \
	t->root = NULL; \
	t->free_node = n; \
	for (i = 0; i < size-1; ++i) { \
		t->free_node[i].right = &t->free_node[i+1]; \
	} \
	t->free_node[size-1].right = NULL; \
}

#define AVL_DEF_ALLOCATE(type, name) \
struct AVL_NODE_NAME(name)* avl_##name##_allocate( \
		struct AVL_TREE_NAME(name)* t) \
{ \
	if (!t->free_node) return NULL; \
	struct AVL_NODE_NAME(name)* ret = t->free_node; \
	t->free_node = t->free_node->right; \
	return ret; \
}

#define AVL_DEF_DEALLOCATE(type, name) \
void avl_##name##_deallocate( \
		struct AVL_TREE_NAME(name)* t, \
		struct AVL_NODE_NAME(name)* n) \
{ \
	if (!t->free_node) { \
		t->free_node = n; \
		n->right = NULL; \
	} else { \
		n->right = t->free_node; \
		t->free_node = n; \
	} \
}

#define AVL_DEF_SEARCH(type, name, compare) \
struct AVL_NODE_NAME(name)* avl_##name##_search( \
		struct AVL_TREE_NAME(name)* t, type val) \
{ \
	struct AVL_NODE_NAME(name)* n = t->root; \
	while (n) { \
		int comp = compare(val, n->value); \
		if (0 < comp) { \
			n = n->left; \
		} else if (comp < 0) { \
			n = n->right; \
		} else { \
			break; \
		} \
	} \
	return n; \
}

#define AVL_NODE_HEIGHT(n) ((n) ? (n)->height : 0)
#define AVL_ROOT_HEIGHT(n) (1 + \
	MAX(AVL_NODE_HEIGHT((n)->left), AVL_NODE_HEIGHT((n)->right)))

#pragma GCC diagnostic ignored "-Waddress"
#pragma GCC diagnostic push
#define AVL_BALANCE_FACTOR(n) ((n) ? \
	AVL_NODE_HEIGHT((n)->left) - AVL_NODE_HEIGHT((n)->right) : 0)
#pragma GCC diagnostic pop

/*
 * from:
 * a
 *  \
 *   b
 *    \
 *     c
 *
 * to:
 *   b
 *  / \
 * a   c
 *
 * alas:
 * 1. b becomes new root
 * 2. a becomes left child of b
 * 3. a takes b's left child as a's right child
 */
#define AVL_DEF_LEFT_ROTATION(type, name) \
struct AVL_NODE_NAME(name)* avl_##name##_left_rotation( \
		struct AVL_NODE_NAME(name)* a) \
{ \
	struct AVL_NODE_NAME(name)* b = a->right; \
	a->right = b->left; /* 3. */ \
	b->left = a; /* 2. */ \
	a->height = AVL_ROOT_HEIGHT(a); \
	b->height = AVL_ROOT_HEIGHT(b); \
	return b; /* 1. */ \
}

/*
 * from:
 *     a
 *    /
 *   b
 *  /
 * c
 *
 * to:
 *   b
 *  / \
 * c   a
 *
 * alas:
 * 1. b becomes new root
 * 2. a becomes b's right child
 * 3. a takes b's right child as a's left child
 */
#define AVL_DEF_RIGHT_ROTATION(type, name) \
struct AVL_NODE_NAME(name)* avl_##name##_right_rotation( \
		struct AVL_NODE_NAME(name)* a) \
{ \
	struct AVL_NODE_NAME(name)* b = a->left; \
	a->left = b->right; /* 3. */ \
	b->right = a; /* 2. */ \
	a->height = AVL_ROOT_HEIGHT(a); \
	b->height = AVL_ROOT_HEIGHT(b); \
	return b; /* 1. */ \
}

#define AVL_DEF_BALANCE(type, name) \
struct AVL_NODE_NAME(name)* avl_##name##_balance( \
		struct AVL_NODE_NAME(name)* n) \
{ \
	if (!n) return n; \
	n->height = AVL_ROOT_HEIGHT(n); \
	int balance_factor = AVL_BALANCE_FACTOR(n); \
	if (balance_factor == -2) { \
		if (AVL_BALANCE_FACTOR(n->right) == 1) { \
			n->right = avl_##name##_right_rotation(n->right); \
		} \
		return avl_##name##_left_rotation(n); \
	} else if (balance_factor == 2) { \
		if (AVL_BALANCE_FACTOR(n->left) == -1) { \
			n->left = avl_##name##_left_rotation(n->left); \
		} \
		return avl_##name##_right_rotation(n); \
	} \
	return n; \
}

#define AVL_DEF_INSERT_R(type, name, compare) \
struct AVL_NODE_NAME(name)* avl_##name##_insert_r( \
		struct AVL_TREE_NAME(name)* t, \
		struct AVL_NODE_NAME(name)* p, \
		struct AVL_NODE_NAME(name)* n, \
		int* ok) \
{ \
	int comp; \
	if (!p) { \
		*ok = 1; \
		return n; \
	} else if (!n) { \
		*ok = 1; \
		return p; \
	} else if (0 < (comp = compare(n->value, p->value))) { \
		p->left = avl_##name##_insert_r(t, p->left, n, ok); \
		return avl_##name##_balance(p); \
	} else if (comp < 0) { \
		p->right = avl_##name##_insert_r(t, p->right, n, ok); \
		return avl_##name##_balance(p); \
	} else { \
		*ok = 0; \
		return p; \
	} \
}

#define AVL_DEF_INSERT(type, name) \
int avl_##name##_insert(struct AVL_TREE_NAME(name)* t, type val) \
{ \
	int ok = 1; \
	struct AVL_NODE_NAME(name) *p, *n; \
	assert(t); \
	n = avl_##name##_allocate(t); \
	if (n == NULL) return 0; \
	n->right = NULL; \
	n->left = NULL; \
	n->value = val; \
	n->height = 1; \
	t->root = avl_##name##_insert_r(t, t->root, n, &ok); \
	if (!ok) avl_##name##_deallocate(t, n); \
	return ok; \
}

#define AVL_DEF_DELETE_R(type, name, compare) \
struct AVL_NODE_NAME(name)* avl_##name##_delete_r( \
		struct AVL_TREE_NAME(name)* t, \
		struct AVL_NODE_NAME(name)* n, \
		type val, int* ok) \
{ \
	struct AVL_NODE_NAME(name)* ret; \
	int comp; \
	assert(t); \
	if (!n) { \
		*ok = 0; \
		return NULL; \
	} else if (0 < (comp = compare(val, n->value))) { \
		n->left = avl_##name##_delete_r(t, n->left, val, ok); \
		return avl_##name##_balance(n); \
	} else if (comp < 0) { \
		n->right = avl_##name##_delete_r(t, n->right, val, ok); \
		return avl_##name##_balance(n); \
	} else { \
		*ok = 1; \
		ret = avl_##name##_insert_r(t, n->right, n->left, &comp); \
		avl_##name##_deallocate(t, n); \
		return avl_##name##_balance(ret); \
	} \
}

#define AVL_DEF_DELETE(type, name) \
int avl_##name##_delete(struct AVL_TREE_NAME(name)* t, type val) { \
	int ok = 0; \
	t->root = avl_##name##_delete_r(t, t->root, val, &ok); \
	return ok; \
}

#define AVL_DEF_PRINT(type, name) \
void avl_##name##_print(struct AVL_TREE_NAME(name)* t, \
		struct AVL_NODE_NAME(name)* qnodes, int size) \
{ \
	int a = 1, b = 0; \
	struct QUEUE_STRUCT(name) q; \
	queue_##name##_init(&q, qnodes, size); \
	if (t->root == NULL) { \
		printf("tree empty\n"); \
		return; \
	} \
	queue_##name##_push(&q, *t->root); \
	while (q.siz > 0) { \
		struct AVL_NODE_NAME(name) n = queue_##name##_pop(&q); \
		if (n.left) { \
			printf("_"); \
			queue_##name##_push(&q, *n.left); \
			++b; \
		} \
		printf("(%d, %d,  %d)", n.value, n.height, \
				AVL_BALANCE_FACTOR(&n)); \
		if (n.right) { \
			printf("_"); \
			queue_##name##_push(&q, *n.right); \
			++b; \
		} \
		printf(" "); \
		if (--a == 0) { \
			a = b; \
			b = 0; \
			printf("\n"); \
		} \
	} \
}

#define AVL_DEFINITIONS(type, name, compare) \
	AVL_DEF_NODE(type, name) \
	AVL_DEF_TREE(type, name) \
	AVL_DEF_INIT(type, name) \
	AVL_DEF_ALLOCATE(type, name) \
	AVL_DEF_DEALLOCATE(type, name) \
	AVL_DEF_SEARCH(type, name, compare) \
	AVL_DEF_LEFT_ROTATION(type, name) \
	AVL_DEF_RIGHT_ROTATION(type, name) \
	AVL_DEF_BALANCE(type, name) \
	AVL_DEF_INSERT_R(type, name, compare) \
	AVL_DEF_INSERT(type, name) \
	AVL_DEF_DELETE_R(type, name, compare) \
	AVL_DEF_DELETE(type, name) \
	QUEUE_DEFINITIONS(struct AVL_NODE_NAME(name), int) \
	AVL_DEF_PRINT(type, name)

