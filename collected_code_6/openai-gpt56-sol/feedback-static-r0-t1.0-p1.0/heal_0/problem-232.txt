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

    if (result == NULL || (data == NULL && count != 0U) || n > count) {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;

    if (n == 0U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*copy)) {
        errno = EOVERFLOW;
        return -1;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return -1;
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
    const int data[] = {12, -4, 38, 7, 38, 19, 2, 25};
    const size_t count = sizeof(data) / sizeof(data[0]);
    const size_t n = 3U;
    int *largest = NULL;

    if (get_n_largest(data, count, n, &largest) != 0) {
        perror("get_n_largest");
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