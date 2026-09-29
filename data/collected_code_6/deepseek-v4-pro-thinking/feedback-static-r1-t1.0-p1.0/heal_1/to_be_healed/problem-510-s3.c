#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    unsigned long long product;
    unsigned long long count;
} ProductCount;

typedef struct {
    ProductCount *items;
    size_t size;
    size_t capacity;
} ProductMap;

static unsigned long long add_ull_sat(unsigned long long a, unsigned long long b) {
    if (a > ULLONG_MAX - b) {
        return ULLONG_MAX;
    }
    return a + b;
}

static unsigned long long mul_ull_sat(unsigned long long a, unsigned long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    if (a > ULLONG_MAX / b) {
        return ULLONG_MAX;
    }
    return a * b;
}

static unsigned long long pow2_ull(int n) {
    if (n >= 64) {
        return ULLONG_MAX;
    }
    return 1ULL << n;
}

/* Possible weaknesses found:
 *  'pow2_minus_one_ull' declared here
 */
static unsigned long long pow2_minus_one_ull(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n >= 64) {
        return ULLONG_MAX;
    }
    return (1ULL << n) - 1ULL;
}

/* Possible weaknesses found:
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 *  to match this '{'
 */
static unsigned long long count_zero_subsequences(int zeros, int positives) {
    if (zeros == 0) {
        return 0;
    }
    /* Possible weaknesses found:
     *  incompatible pointer to integer conversion initializing 'unsigned long long' with an expression of type 'unsigned long long (int)' [-Wint-conversion]
     *  expected ',' or ';' at end of input
     *  expected ';' at end of declaration
     *  'pow2_minus_one' undeclared (first use in this function); did you mean 'pow2_minus_one_ull'?
     *  use of undeclared identifier 'pow2_minus_one'; did you mean 'pow2_minus_one_ull'?
     *  expected declaration or statement at end of input
     *  each undeclared identifier is reported only once for each function it appears in
     *  expected '}'
     */
    unsigned long long zsub = pow2_minus_one