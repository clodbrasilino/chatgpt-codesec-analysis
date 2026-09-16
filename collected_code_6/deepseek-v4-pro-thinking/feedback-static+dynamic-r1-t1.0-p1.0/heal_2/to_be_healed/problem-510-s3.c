#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'ProductCount::product' is never used. [unusedStructMember]
     */
    unsigned long long product;
    /* Possible weaknesses found:
     *  struct member 'ProductCount::count' is never used. [unusedStructMember]
     */
    unsigned long long count;
} ProductCount;

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'ProductMap::items' is never used. [unusedStructMember]
     */
    ProductCount *items;
    /* Possible weaknesses found:
     *  struct member 'ProductMap::size' is never used. [unusedStructMember]
     */
    size_t size;
    /* Possible weaknesses found:
     *  struct member 'ProductMap::capacity' is never used. [unusedStructMember]
     */
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

static unsigned long long pow2_minus_one_ull(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n >= 64) {
        return ULLONG_MAX;
    }
    return (1ULL << n) - 1ULL;
}

static unsigned long long count_zero_subsequences(int zeros, int positives) {
    if (zeros == 0) {
        return 0;
    }
    unsigned long long zsub = pow2_minus_one_ull(zeros);
    unsigned long long psub = pow2_ull(positives);
    return mul_ull_sat(zsub, psub);
}

int main(void) {
    int zeros = 2;
    int positives = 3;
    unsigned long long result = count_zero_subsequences(zeros, positives);
    printf("zeros = %d, positives = %d -> %llu\n", zeros, positives, result);
    return 0;
}