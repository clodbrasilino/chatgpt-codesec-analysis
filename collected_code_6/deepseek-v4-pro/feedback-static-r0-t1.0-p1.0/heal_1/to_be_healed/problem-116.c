#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int compare_unsigned(const void *a, const void *b) {
    unsigned int ua = *(const unsigned int *)a;
    unsigned int ub = *(const unsigned int *)b;
    if (ua < ub) return -1;
    if (ua > ub) return 1;
    return 0;
}

int tuple_to_integer(unsigned int *values, size_t count, uint64_t *result) {
    unsigned int *sorted = NULL;
    uint64_t accumulator = 0;
    unsigned int prev = 0;
    size_t i;

    if (values == NULL || result == NULL) {
        return -1;
    }

    if (count == 0) {
        *result = 0;
        return 0;
    }

    sorted = (unsigned int *)malloc(count * sizeof(unsigned int));
    if (sorted == NULL) {
        return -1;
    }

    memcpy(sorted, values, count * sizeof(unsigned int));
    qsort(sorted, count, sizeof(unsigned int), compare_unsigned);

    accumulator = (uint64_t)sorted[0];
    prev = sorted[0];

    for (i = 1; i < count; i++) {
        uint64_t factor = 1;
        unsigned int curr = sorted[i];
        uint64_t base = (uint64_t)prev + 1;

        if (curr == prev) {
            factor = 0;
        } else {
            /* Possible weaknesses found:
             *  Value stored to 'range' during its initialization is never read [deadcode.DeadStores]
             *  Variable 'range' is assigned a value that is never used. [unreadVariable]
             */
            uint64_t range = (uint64_t)curr - (uint64_t)prev;
            if (UINT64_MAX / base < factor) {
                free(sorted);
                return -1;
            }
            factor = base;
        }

        if (factor > 0) {
            if (UINT64_MAX - accumulator < factor) {
                free(sorted);
                return -1;
            }
            accumulator += factor;
        }

        prev = curr;
    }

    free(sorted);
    *result = accumulator;
    return 0;
}

int main(void) {
    const unsigned int tuple1[] = {3, 1, 4, 1, 5, 9, 2, 6};
    const unsigned int tuple2[] = {10, 7, 23};
    const unsigned int tuple3[] = {5};
    const unsigned int tuple4[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    const unsigned int tuple5[] = {100, 50, 25};
    uint64_t result;
    int ret;

    ret = tuple_to_integer((unsigned int *)tuple1, sizeof(tuple1)/sizeof(tuple1[0]), &result);
    if (ret == 0) {
        printf("tuple1 -> %llu\n", (unsigned long long)result);
    } else {
        printf("tuple1 conversion failed\n");
    }

    ret = tuple_to_integer((unsigned int *)tuple2, sizeof(tuple2)/sizeof(tuple2[0]), &result);
    if (ret == 0) {
        printf("tuple2 -> %llu\n", (unsigned long long)result);
    } else {
        printf("tuple2 conversion failed\n");
    }

    ret = tuple_to_integer((unsigned int *)tuple3, sizeof(tuple3)/sizeof(tuple3[0]), &result);
    if (ret == 0) {
        printf("tuple3 -> %llu\n", (unsigned long long)result);
    } else {
        printf("tuple3 conversion failed\n");
    }

    ret = tuple_to_integer((unsigned int *)tuple4, sizeof(tuple4)/sizeof(tuple4[0]), &result);
    if (ret == 0) {
        printf("tuple4 -> %llu\n", (unsigned long long)result);
    } else {
        printf("tuple4 conversion failed\n");
    }

    ret = tuple_to_integer((unsigned int *)tuple5, sizeof(tuple5)/sizeof(tuple5[0]), &result);
    if (ret == 0) {
        printf("tuple5 -> %llu\n", (unsigned long long)result);
    } else {
        printf("tuple5 conversion failed\n");
    }

    ret = tuple_to_integer(NULL, 3, &result);
    if (ret == 0) {
        printf("null values -> %llu\n", (unsigned long long)result);
    } else {
        printf("null values conversion failed\n");
    }

    ret = tuple_to_integer((unsigned int *)tuple1, 3, NULL);
    if (ret == 0) {
        printf("null result -> %llu\n", (unsigned long long)result);
    } else {
        printf("null result conversion failed\n");
    }

    ret = tuple_to_integer((unsigned int *)tuple1, 0, &result);
    if (ret == 0) {
        printf("empty tuple -> %llu\n", (unsigned long long)result);
    } else {
        printf("empty tuple conversion failed\n");
    }

    return 0;
}