#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool multiply_checked(long long left, int right, long long *result)
{
    if (right > 0) {
        if (left > LLONG_MAX / right || left < LLONG_MIN / right) {
            return false;
        }
    } else if (right < 0) {
        if (right == -1) {
            if (left == LLONG_MIN) {
                return false;
            }
        } else if (left > LLONG_MIN / right || left < LLONG_MAX / right) {
            return false;
        }
    }

    *result = left * right;
    return true;
}

static bool product_of_unique_numbers(int *numbers, size_t count,
                                      long long *product)
{
    long long value = 1;

    if (numbers == NULL || product == NULL || count == 0U) {
        return false;
    }

    qsort(numbers, count, sizeof(*numbers), compare_ints);

    for (size_t i = 0U; i < count; ++i) {
        if (i == 0U || numbers[i] != numbers[i - 1U]) {
            if (!multiply_checked(value, numbers[i], &value)) {
                return false;
            }
        }
    }

    *product = value;
    return true;
}

int main(void)
{
    size_t count;
    int *numbers = NULL;
    long long product;
    int status = EXIT_FAILURE;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Invalid list size\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            goto cleanup;
        }
    }

    if (!product_of_unique_numbers(numbers, count, &product)) {
        fprintf(stderr, "Product overflow or invalid input\n");
        goto cleanup;
    }

    if (printf("%lld\n", product) < 0) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(numbers);
    return status;
}