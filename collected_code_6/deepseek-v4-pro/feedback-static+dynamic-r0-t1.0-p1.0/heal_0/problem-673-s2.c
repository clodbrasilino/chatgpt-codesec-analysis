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
    int negative = 0;
    size_t i = 0;

    if (list[0] < 0) {
        negative = 1;
        i = 1;
    }

    for (; i < count; i++) {
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

    return negative ? -result : result;
}

int main(void) {
    int numbers1[] = {1, 2, 3, 4, 5};
    int numbers2[] = {-1, 2, 3};
    int numbers3[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    int numbers4[] = {1, -2, 3};
    int numbers5[] = {1, 10, 3};

    errno = 0;
    long long result1 = list_to_integer(numbers1, sizeof(numbers1) / sizeof(numbers1[0]));
    printf("Result 1: %lld (errno: %d)\n", result1, errno);

    errno = 0;
    long long result2 = list_to_integer(numbers2, sizeof(numbers2) / sizeof(numbers2[0]));
    printf("Result 2: %lld (errno: %d)\n", result2, errno);

    errno = 0;
    long long result3 = list_to_integer(numbers3, sizeof(numbers3) / sizeof(numbers3[0]));
    printf("Result 3: %lld (errno: %d)\n", result3, errno);

    errno = 0;
    long long result4 = list_to_integer(numbers4, sizeof(numbers4) / sizeof(numbers4[0]));
    printf("Result 4: %lld (errno: %d)\n", result4, errno);

    errno = 0;
    long long result5 = list_to_integer(numbers5, sizeof(numbers5) / sizeof(numbers5[0]));
    printf("Result 5: %lld (errno: %d)\n", result5, errno);

    errno = 0;
    long long result6 = list_to_integer(NULL, 0);
    printf("Result 6: %lld (errno: %d)\n", result6, errno);

    return 0;
}