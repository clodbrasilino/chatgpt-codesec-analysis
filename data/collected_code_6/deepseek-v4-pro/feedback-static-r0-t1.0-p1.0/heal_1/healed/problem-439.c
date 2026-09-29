#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long list_to_integer(const int *list, size_t count) {
    if (list == NULL || count == 0) {
        errno = EINVAL;
        return 0;
    }

    long long result = 0;
    int sign = 1;
    size_t start = 0;

    if (list[0] < 0) {
        sign = -1;
        start = 1;
        if (count == 1) {
            errno = EINVAL;
            return 0;
        }
    }

    for (size_t i = start; i < count; i++) {
        if (list[i] < 0 || list[i] > 9) {
            errno = EINVAL;
            return 0;
        }

        if (result > (LLONG_MAX - list[i]) / 10) {
            errno = ERANGE;
            return 0;
        }

        result = result * 10 + list[i];
    }

    return sign * result;
}

int main(void) {
    const int test1[] = {1, 2, 3, 4, 5};
    long long val1 = list_to_integer(test1, 5);
    if (errno == 0) {
        printf("%lld\n", val1);
    } else {
        printf("Error\n");
    }

    const int test2[] = {-1, 5, 0};
    errno = 0;
    long long val2 = list_to_integer(test2, 3);
    if (errno == 0) {
        printf("%lld\n", val2);
    } else {
        printf("Error\n");
    }

    const int test3[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    errno = 0;
    long long val3 = list_to_integer(test3, 19);
    if (errno == 0) {
        printf("%lld\n", val3);
    } else {
        printf("Error\n");
    }

    const int test4[] = {10, 2, 3};
    errno = 0;
    long long val4 = list_to_integer(test4, 3);
    if (errno == 0) {
        printf("%lld\n", val4);
    } else {
        printf("Error\n");
    }

    return 0;
}