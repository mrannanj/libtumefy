#include <stdio.h>
#include <stddef.h>

#include "common.h"
#include "search.h"

#define TEST_LESS(a, b) (a < b)
DEFINE_SEARCH_FUNCTIONS(int, int, TEST_LESS)

int main() {
	int i;
	int A[11] = {0, 1, 2, 4, 4, 4, 6, 10, 10, 10, 10};
	/*           0  1  2  3  4  5  6   7   8   9  10*/

	int len = sizeof(A)/sizeof(A[0]);

	assert_eq(binsearch_int(A, len, 0), 0);
	assert_eq(binsearch_int(A, len, 1), 1);
	assert_eq(binsearch_int(A, len, 2), 2);
	assert_eq(binsearch_int(A, len, 6), 6);

	assert_eq(upper_bound_int(A, len, 0), 1);
	assert_eq(upper_bound_int(A, len, 1), 2);
	assert_eq(upper_bound_int(A, len, 2), 3);
	assert_eq(upper_bound_int(A, len, 3), 3);
	assert_eq(upper_bound_int(A, len, 4), 6);
	assert_eq(upper_bound_int(A, len, 5), 6);
	assert_eq(upper_bound_int(A, len, 6), 7);
	assert_eq(upper_bound_int(A, len, 7), 7);
	assert_eq(upper_bound_int(A, len, 8), 7);
	assert_eq(upper_bound_int(A, len, 9), 7);
	assert_eq(upper_bound_int(A, len, 10), 11);
	assert_eq(upper_bound_int(A, len, 11), 11);

	/*t A[11] = {0, 1, 2, 4, 4, 4, 6, 10, 10, 10, 10}; */
	/*           0  1  2  3  4  5  6   7   8   9  10   */

	assert_eq(lower_bound_int(A, len, 0), 0);
	assert_eq(lower_bound_int(A, len, 1), 1);
	assert_eq(lower_bound_int(A, len, 2), 2);
	assert_eq(lower_bound_int(A, len, 3), 3);
	assert_eq(lower_bound_int(A, len, 4), 3);
	assert_eq(lower_bound_int(A, len, 5), 6);
	assert_eq(lower_bound_int(A, len, 6), 6);
	assert_eq(lower_bound_int(A, len, 7), 7);
	assert_eq(lower_bound_int(A, len, 8), 7);
	assert_eq(lower_bound_int(A, len, 9), 7);
	assert_eq(lower_bound_int(A, len, 10), 7);

	return 0;
}
