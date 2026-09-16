#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *first, const void *second)
{
    const int a = *(const int *)first;
    const int b = *(const int *)second;

    return (a > b) - (a < b);
}

static long long sum_non_repeated(const int array[], size_t length)
{
    long long sum = 0;
    size_t index = 0;

    while (index < length) {
        size_t next = index + 1;

        while (next < length && array[next] == array[index]) {
            ++next;
        }

        if (next == index + 1) {
            sum += array[index];
        }

        index = next;
    }

    return sum;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    qsort(array, length, sizeof(*array), compare_ints);
    printf("%lld\n", sum_non_repeated(array, length));

    free(array);
    return EXIT_SUCCESS;
}