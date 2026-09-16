#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_descending(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (b > a) - (b < a);
}

static int get_n_largest(const int *data, size_t count, size_t n, int **result)
{
    int *copy;

    if (result == NULL || n > count || (data == NULL && count != 0U)) {
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

    qsort(copy, count, sizeof(*copy), compare_descending);

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
    const int data[] = {12, 5, 87, 34, 19, 87, -4, 56, 42};
    const size_t count = sizeof(data) / sizeof(data[0]);
    const size_t n = 4U;
    int *largest = NULL;
    int status = get_n_largest(data, count, n, &largest);

    if (status != 0) {
        fprintf(stderr, "get_n_largest failed: %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < n; ++i) {
        printf("%d%s", largest[i], i + 1U == n ? "\n" : " ");
    }

    free(largest);
    return EXIT_SUCCESS;
}