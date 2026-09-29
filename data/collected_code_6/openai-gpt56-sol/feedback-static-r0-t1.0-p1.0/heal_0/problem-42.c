#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int compare_int64(const void *left, const void *right)
{
    const int64_t a = *(const int64_t *)left;
    const int64_t b = *(const int64_t *)right;

    return (a > b) - (a < b);
}

static int sum_repeated_elements(const int64_t *array, size_t length, int64_t *sum)
{
    int64_t *copy;
    size_t i;
    int64_t result = 0;

    if (array == NULL || sum == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_int64);

    i = 0;
    while (i < length) {
        size_t j = i + 1;

        while (j < length && copy[j] == copy[i]) {
            ++j;
        }

        if (j - i > 1) {
            if ((copy[i] > 0 && result > INT64_MAX - copy[i]) ||
                (copy[i] < 0 && result < INT64_MIN - copy[i])) {
                free(copy);
                return -1;
            }
            result += copy[i];
        }

        i = j;
    }

    free(copy);
    *sum = result;
    return 0;
}

int main(void)
{
    int64_t array[] = {1, 2, 3, 2, 4, 3, 3, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int64_t sum;

    errno = 0;
    if (sum_repeated_elements(array, length, &sum) != 0) {
        if (errno != 0) {
            perror("sum_repeated_elements");
        } else {
            fputs("Unable to calculate the sum\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}