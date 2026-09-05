#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int64_t convert_tuple_to_int(const unsigned int *tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        return -1;
    }

    int64_t result = 0;

    for (size_t i = 0; i < size; ++i) {
        if (tuple[i] > 9) {
            return -1;
        }

        if (result > (INT64_MAX - tuple[i]) / 10) {
            return -1;
        }

        result = result * 10 + tuple[i];
    }

    return result;
}

int main(void) {
    unsigned int t1[] = {1, 2, 3, 4};
    size_t s1 = sizeof(t1) / sizeof(t1[0]);
    int64_t r1 = convert_tuple_to_int(t1, s1);
    if (r1 != -1) {
        printf("%lld\n", (long long)r1);
    }

    unsigned int t2[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    size_t s2 = sizeof(t2) / sizeof(t2[0]);
    int64_t r2 = convert_tuple_to_int(t2, s2);
    if (r2 == -1) {
        printf("Overflow handled\n");
    }

    return 0;
}