#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int find_kth_smallest(const int array[], size_t length, size_t k, int *result)
{
    int *copy;

    if (array == NULL || result == NULL || length == 0U || k == 0U || k > length) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*copy)) {
        return 0;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);
    *result = copy[k - 1U];

    free(copy);
    return 1;
}

int main(void)
{
    int array[] = {7, 2, 9, 4, 1, 6};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t k;
    int result;

    if (printf("Enter k (1-%zu): ", length) < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!find_kth_smallest(array, length, k, &result)) {
        fprintf(stderr, "Unable to find the requested element.\n");
        return EXIT_FAILURE;
    }

    if (printf("The %zuth smallest element is %d.\n", k, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}