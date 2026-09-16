#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static int min_subsets_distinct(const int *arr, size_t n)
{
    int *copy;
    int max_count;
    int count;
    size_t i;

    if (arr == NULL || n == 0) {
        return 0;
    }

    copy = malloc(n * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    qsort(copy, n, sizeof(*copy), compare_ints);

    max_count = 1;
    count = 1;

    for (i = 1; i < n; i++) {
        if (copy[i] == copy[i - 1]) {
            count++;
            if (count > max_count) {
                max_count = count;
            }
        } else {
            count = 1;
        }
    }

    free(copy);
    return max_count;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 4, 4, 5, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result;

    result = min_subsets_distinct(arr, n);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum number of subsets with distinct elements: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}