#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int compare_intmax(const void *lhs, const void *rhs)
{
    const intmax_t a = *(const intmax_t *)lhs;
    const intmax_t b = *(const intmax_t *)rhs;

    return (a > b) - (a < b);
}

static int sum_repeated_elements(const intmax_t *array, size_t length, intmax_t *sum)
{
    intmax_t *copy = NULL;
    intmax_t result = 0;
    size_t i = 0;

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

    qsort(copy, length, sizeof(*copy), compare_intmax);

    i = 0;
    while (i < length) {
        size_t j = i + 1;

        while (j < length && copy[j] == copy[i]) {
            ++j;
        }

        if (j - i > 1) {
            if ((copy[i] > 0 && result > INTMAX_MAX - copy[i]) ||
                (copy[i] < 0 && result < INTMAX_MIN - copy[i])) {
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
    intmax_t values[] = {1, 2, 3, 2, 4, 3, 3, 5};
    const size_t length = sizeof(values) / sizeof(values[0]);
    intmax_t sum = 0;

    errno = 0;
    if (sum_repeated_elements(values, length, &sum) != 0) {
        if (errno != 0) {
            perror("sum_repeated_elements");
        } else {
            fputs("Unable to calculate the sum\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("Sum of repeated elements: %" PRIdMAX "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}