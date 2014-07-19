#pragma once

#define QUEUE_STRUCT(name) queue_##name

#define QUEUE_DEF_STRUCT(type, name) \
struct QUEUE_STRUCT(name) { \
	type* Q; \
	int cap; \
	int siz; \
	int fst; \
	int lst; \
};

#define QUEUE_DEF_INIT(type, name) \
void queue_##name##_init(struct QUEUE_STRUCT(name)* q, type *A, int cap) \
{ \
	q->Q = A; \
	q->cap = cap; \
	q->siz = 0; \
	q->fst = 0; \
	q->lst = 0; \
}

#define QUEUE_DEF_PUSH(type, name) \
int queue_##name##_push(struct QUEUE_STRUCT(name)* q, type x) { \
	if (q->siz+1 > q->cap) return 0; \
	++q->siz; \
	q->Q[q->lst++] = x; \
	return 1; \
}

#define QUEUE_DEF_POP(type, name) \
type queue_##name##_pop(struct QUEUE_STRUCT(name)* q) { \
	assert(q->siz > 0); \
	--q->siz; \
	return q->Q[q->fst++]; \
}

#define QUEUE_DEFINITIONS(type, name) \
	QUEUE_DEF_STRUCT(type, name) \
	QUEUE_DEF_INIT(type, name) \
	QUEUE_DEF_PUSH(type, name) \
	QUEUE_DEF_POP(type, name)

