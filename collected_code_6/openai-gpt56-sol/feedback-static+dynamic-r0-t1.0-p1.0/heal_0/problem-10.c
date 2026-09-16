#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int get_n_smallest(const int *data, size_t count, size_t n, int **result)
{
    int *copy;

    if (result == NULL || (data == NULL && count != 0U) || n > count) {
        return EINVAL;
    }

    *result = NULL;

    if (n == 0U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*copy)) {
        return EOVERFLOW;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0U; i < count; ++i) {
        copy[i] = data[i];
    }

    qsort(copy, count, sizeof(*copy), compare_ints);

    if (n < count) {
        int *resized = realloc(copy, n * sizeof(*copy));
        if (resized != NULL) {
            copy = resized;
        }
    }

    *result = copy;
    return 0;
}

int main(void)
{
    int dataset[] = {42, 7, -3, 19, 7, 0, 88, 5};
    const size_t count = sizeof(dataset) / sizeof(dataset[0]);
    const size_t n = 4U;
    int *smallest = NULL;
    int status = get_n_smallest(dataset, count, n, &smallest);

    if (status != 0) {
        fprintf(stderr, "get_n_smallest failed: %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < n; ++i) {
        if (printf("%d%s", smallest[i], i + 1U == n ? "\n" : " ") < 0) {
            free(smallest);
            return EXIT_FAILURE;
        }
    }

    free(smallest);
    return EXIT_SUCCESS;
}