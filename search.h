#define DEFINE_BINSEARCH(type, id, less) \
int binsearch_##id(type A[], int len, type x) { \
	int l = 0; \
	int r = len-1; \
	while (l <= r) { \
		int mid = l + ((r-l)>>1); \
		type cur = A[mid]; \
		if (less(x, cur)) { \
			r = mid - 1; \
		} else if (less(cur, x)) { \
			l = mid + 1; \
		} else { \
			return mid; \
		} \
	} \
	return -1; \
}

#define DEFINE_UPPER_BOUND(type, id, less) \
int upper_bound_##id(type A[], int len, type x) { \
	int l = 0; \
	int r = len; \
	while (l < r) { \
		int mid = l + ((r-l)>>1); \
		type cur = A[mid]; \
		if (less(x, cur)) { \
			r = mid; \
		} else { \
			l = mid + 1; \
		} \
	} \
	return r; \
}

#define DEFINE_LOWER_BOUND(type, id, less) \
int lower_bound_##id(type A[], int len, type x) { \
	int l = 0; \
	int r = len; \
	while (l < r) { \
		int mid = l + ((r-l)>>1); \
		type cur = A[mid]; \
		if (!less(cur, x)) { \
			r = mid; \
		} else { \
			l = mid + 1; \
		} \
	} \
	return l; \
}

#define DEFINE_SEARCH_FUNCTIONS(type, id, less) \
	DEFINE_LOWER_BOUND(type, id, less) \
	DEFINE_UPPER_BOUND(type, id, less) \
	DEFINE_BINSEARCH(type, id, less)

