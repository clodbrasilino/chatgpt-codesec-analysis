#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int left = *(const int *)lhs;
    const int right = *(const int *)rhs;

    return (left > right) - (left < right);
}

static int get_n_smallest(const int *dataset, size_t count, size_t n, int **result)
{
    int *copy;

    if (result == NULL || (dataset == NULL && count != 0U) || n > count) {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;

    if (n == 0U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*copy) || n > SIZE_MAX / sizeof(**result)) {
        errno = EOVERFLOW;
        return -1;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        copy[i] = dataset[i];
    }

    qsort(copy, count, sizeof(*copy), compare_ints);

    *result = malloc(n * sizeof(**result));
    if (*result == NULL) {
        free(copy);
        return -1;
    }

    for (size_t i = 0U; i < n; ++i) {
        (*result)[i] = copy[i];
    }

    free(copy);
    return 0;
}

int main(void)
{
    const int dataset[] = {42, 7, -3, 19, 0, 12, -8, 5};
    const size_t count = sizeof(dataset) / sizeof(dataset[0]);
    const size_t n = 4U;
    int *smallest = NULL;

    if (get_n_smallest(dataset, count, n, &smallest) != 0) {
        perror("get_n_smallest");
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