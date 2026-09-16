#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int find_equilibrium_index(const long long *array, size_t length, size_t *index)
{
    long long total = 0;
    long long left_sum = 0;

    if (array == NULL || index == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (__builtin_add_overflow(total, array[i], &total)) {
            return 0;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        long long right_sum;

        if (__builtin_sub_overflow(total, left_sum, &right_sum) ||
            __builtin_sub_overflow(right_sum, array[i], &right_sum)) {
            return 0;
        }

        if (left_sum == right_sum) {
            *index = i;
            return 1;
        }

        if (__builtin_add_overflow(left_sum, array[i], &left_sum)) {
            return 0;
        }
    }

    return 0;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(long long)) {
        return EXIT_FAILURE;
    }

    long long *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%lld", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    size_t index;
    int found = find_equilibrium_index(array, length, &index);

    free(array);

    if (found) {
        printf("%zu\n", index);
    } else {
        printf("-1\n");
    }

    return EXIT_SUCCESS;
}