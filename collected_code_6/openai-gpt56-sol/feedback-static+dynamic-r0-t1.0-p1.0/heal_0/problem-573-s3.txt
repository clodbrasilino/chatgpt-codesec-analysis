#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int multiply_checked(long long a, int b, long long *result)
{
    if (b > 0 && (a > LLONG_MAX / b || a < LLONG_MIN / b)) {
        return 0;
    }

    if (b < 0) {
        if ((a > 0 && b < LLONG_MIN / a) ||
            (a < 0 && a < LLONG_MAX / b)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int product_of_unique_numbers(int *numbers, size_t count,
                                     long long *product)
{
    long long result = 1;

    if (numbers == NULL || product == NULL || count == 0U) {
        return 0;
    }

    qsort(numbers, count, sizeof(*numbers), compare_ints);

    for (size_t i = 0U; i < count;) {
        size_t next = i + 1U;

        while (next < count && numbers[next] == numbers[i]) {
            ++next;
        }

        if (next - i == 1U &&
            !multiply_checked(result, numbers[i], &result)) {
            return 0;
        }

        i = next;
    }

    *product = result;
    return 1;
}

int main(void)
{
    size_t count;
    int *numbers = NULL;
    long long product;

    if (scanf("%zu", &count) != 1 || count == 0U ||
        count > SIZE_MAX / sizeof(*numbers)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &numbers[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    if (!product_of_unique_numbers(numbers, count, &product)) {
        fputs("Unable to calculate product\n", stderr);
        free(numbers);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", product) < 0) {
        fputs("Output error\n", stderr);
        free(numbers);
        return EXIT_FAILURE;
    }

    free(numbers);
    return EXIT_SUCCESS;
}