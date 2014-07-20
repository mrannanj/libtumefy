#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void assert_eq_(int32_t a, int32_t b, int ln) {
	if (a == b) return;
	printf("%d: %d != %d\n", ln, a, b);
	exit(0);
}

#define assert_eq(a, b) assert_eq_(a, b, __LINE__)

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

