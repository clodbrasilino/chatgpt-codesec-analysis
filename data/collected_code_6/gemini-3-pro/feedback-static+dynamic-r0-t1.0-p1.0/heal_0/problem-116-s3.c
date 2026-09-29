#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

long long tuple_to_int(const int* tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        return -1;
    }

    long long result = 0;

    for (size_t i = 0; i < size; ++i) {
        if (tuple[i] < 0) {
            return -1;
        }

        int temp = tuple[i];
        long long multiplier = 1;

        if (temp == 0) {
            multiplier = 10;
        } else {
            while (temp > 0) {
                if (LLONG_MAX / 10 < multiplier) {
                    return -1;
                }
                multiplier *= 10;
                temp /= 10;
            }
        }

        if (LLONG_MAX / multiplier < result) {
            return -1;
        }
        
        result *= multiplier;

        if (LLONG_MAX - result < tuple[i]) {
            return -1;
        }

        result += tuple[i];
    }

    return result;
}

int main(void) {
    int tuple1[] = {1, 2, 3};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    long long res1 = tuple_to_int(tuple1, size1);
    if (res1 != -1) {
        printf("%lld\n", res1);
    } else {
        printf("Error\n");
    }

    int tuple2[] = {45, 6, 78};
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    long long res2 = tuple_to_int(tuple2, size2);
    if (res2 != -1) {
        printf("%lld\n", res2);
    } else {
        printf("Error\n");
    }

    int tuple3[] = {0, 5, 0};
    size_t size3 = sizeof(tuple3) / sizeof(tuple3[0]);
    long long res3 = tuple_to_int(tuple3, size3);
    if (res3 != -1) {
        printf("%lld\n", res3);
    } else {
        printf("Error\n");
    }

    return 0;
}