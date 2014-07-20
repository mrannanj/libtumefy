#pragma once

#include <limits.h>

#include "common.h"

#define ST_STRUCT_NAME(name) st_##name

#define ST_DEF_STRUCT(type, name) \
struct ST_STRUCT_NAME(name) { \
	int size; \
	struct type* tree; \
};

#define ST_DEF_INIT(type, name) \
void st_##name##_init(struct ST_STRUCT_NAME(name)* st, int size, \
		struct type* tree) { \
	assert(st); \
	st->size = size; \
	st->tree = tree; \
	memset(st->tree, 0, sizeof(tree[0]) * st->size); \
}

#define ST_DEF_UPDATE_R(type, name, split, merge, update) \
void st_##name##_update_r(struct ST_STRUCT_NAME(name)* st, \
		int qs, int qe, int ns, int ne, int i, int x) { \
	struct type left, right; \
	int mid; \
	if (i >= st->size || qs == qe || ns == ne || ne <= qs || qe <= ns) { \
	} else if (qs <= ns && ne <= qe) { \
		update(st->tree[i], x); \
	} else { \
		mid = ns + ((ne-ns)>>1); \
		split(st->tree[i], st->tree[i<<1], st->tree[(i<<1)+1]); \
		st_##name##_update_r(st, qs, qe, ns, mid, i<<1, x); \
		st_##name##_update_r(st, qs, qe, mid, ne, (i<<1)+1, x); \
		merge(st->tree[i], st->tree[i<<1], st->tree[(i<<1)+1]); \
	} \
}

#define ST_DEF_UPDATE(type, name) \
void st_##name##_update(struct ST_STRUCT_NAME(name)* st, \
		int qs, int qe, int x) { \
	st_##name##_update_r(st, qs, qe, 0, st->size>>1, 1, x); \
}

#define ST_DEF_QUERY_R(type, name, split, merge, identity) \
struct type st_##name##_query_r(struct ST_STRUCT_NAME(name)* st, \
		int qs, int qe, int ns, int ne, int i) \
{ \
	struct type left, right, ret; \
	int mid; \
	if (i >= st->size || qs == qe || ns == ne || ne <= qs || qe <= ns) { \
		return identity; \
	} else if (qs <= ns && ne <= qe) { \
		return st->tree[i]; \
	} else { \
		mid = ns + ((ne-ns)>>1); \
		split(st->tree[i], st->tree[i<<1], st->tree[(i<<1)+1]); \
		left = st_##name##_query_r(st, qs, qe, ns, mid, i<<1); \
		right = st_##name##_query_r(st, qs, qe, mid, ne, (i<<1)+1); \
		merge(st->tree[i], st->tree[i<<1], st->tree[(i<<1)+1]); \
		merge(ret, left, right); \
		return ret; \
	} \
}

#define ST_DEF_QUERY(type, name) \
struct type st_##name##_query(struct ST_STRUCT_NAME(name)* st, \
		int qs, int qe) { \
	return st_##name##_query_r(st, qs, qe, 0, st->size>>1, 1); \
}

#define ST_DEF_PRINT(type, name, print) \
void st_##name##_print(struct ST_STRUCT_NAME(name)* st) { \
	int i, lvl_cur = 0, lvl_max = 1; \
	for (i = 1; i < st->size; ++i) { \
		print(st->tree[i]); \
		lvl_cur += 1; \
		if (lvl_cur == lvl_max) { \
			lvl_max <<= 1; \
			lvl_cur = 0; \
			printf("\n"); \
		} \
	} \
	printf("\n"); \
}

#define ST_DEFINITIONS(type, name, split, merge, update, identity, print) \
	ST_DEF_STRUCT(type, name) \
	ST_DEF_INIT(type, name) \
	ST_DEF_UPDATE_R(type, name, split, merge, update) \
	ST_DEF_UPDATE(type, name) \
	ST_DEF_QUERY_R(type, name, split, merge, identity) \
	ST_DEF_QUERY(type, name) \
	ST_DEF_PRINT(type, name, print)

