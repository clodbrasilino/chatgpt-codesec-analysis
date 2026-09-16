#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long tuple_to_int(const unsigned int *tuple, size_t size) {
    if (tuple == NULL) {
        return 0;
    }

    unsigned long long result = 0;
    for (size_t i = 0; i < size; i++) {
        unsigned int val = tuple[i];
        unsigned long long shift = 1;
        while (val >= 10) {
            shift *= 10;
            if (shift == 0) {
                return 0;
            }
            val /= 10;
        }
        if (result > (ULLONG_MAX - (tuple[i] % shift)) / (shift * 10)) {
            return 0;
        }
        result = result * shift * 10 + tuple[i];
    }
    return result;
}

int main(void) {
    unsigned int t1[] = {1, 2, 3};
    size_t s1 = sizeof(t1) / sizeof(t1[0]);
    unsigned long long r1 = tuple_to_int(t1, s1);
    printf("%llu\n", r1);

    unsigned int t2[] = {12, 34, 5};
    size_t s2 = sizeof(t2) / sizeof(t2[0]);
    unsigned long long r2 = tuple_to_int(t2, s2);
    printf("%llu\n", r2);

    unsigned long long r3 = tuple_to_int(NULL, 0);
    printf("%llu\n", r3);

    return 0;
}