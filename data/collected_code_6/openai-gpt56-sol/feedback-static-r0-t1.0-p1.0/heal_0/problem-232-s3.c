#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_int_descending(const void *lhs, const void *rhs)
{
    const int left = *(const int *)lhs;
    const int right = *(const int *)rhs;

    return (right > left) - (right < left);
}

static int get_n_largest(const int *data, size_t count, size_t n, int **result)
{
    int *copy;

    if (result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if ((data == NULL && count != 0U) || n > count) {
        return EINVAL;
    }

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

    qsort(copy, count, sizeof(*copy), compare_int_descending);

    if (n < count) {
        int *smaller = realloc(copy, n * sizeof(*copy));
        if (smaller != NULL) {
            copy = smaller;
        }
    }

    *result = copy;
    return 0;
}

int main(void)
{
    const int dataset[] = {42, 7, 19, 93, 55, 31, 93, -4, 68, 12};
    const size_t count = sizeof(dataset) / sizeof(dataset[0]);
    const size_t n = 4U;
    int *largest = NULL;
    int status = get_n_largest(dataset, count, n, &largest);

    if (status != 0) {
        fprintf(stderr, "get_n_largest failed: %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < n; ++i) {
        if (printf("%d%s", largest[i], i + 1U == n ? "\n" : " ") < 0) {
            free(largest);
            return EXIT_FAILURE;
        }
    }

    free(largest);
    return EXIT_SUCCESS;
}