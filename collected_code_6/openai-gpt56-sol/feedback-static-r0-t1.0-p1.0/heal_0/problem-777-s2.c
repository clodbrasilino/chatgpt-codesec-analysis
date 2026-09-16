#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

int sum_non_repeated(const int *array, size_t length, long long *sum)
{
    int *copy;
    size_t i;

    if (array == NULL || sum == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*copy)) {
        return 0;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    *sum = 0;
    i = 0;

    while (i < length) {
        size_t next = i + 1;

        while (next < length && copy[next] == copy[i]) {
            ++next;
        }

        if (next == i + 1) {
            *sum += copy[i];
        }

        i = next;
    }

    free(copy);
    return 1;
}

int main(void)
{
    int array[] = {1, 2, 3, 2, 4, 1, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    long long sum;

    if (!sum_non_repeated(array, length, &sum)) {
        fputs("Unable to calculate the sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}