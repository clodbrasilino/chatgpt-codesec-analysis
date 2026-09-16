#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int add_consecutive(const int *values, size_t count, long long *result)
{
    size_t i;
    long long sum = 0;

    if (result == NULL || (values == NULL && count != 0U)) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if ((values[i] > 0 && sum > LLONG_MAX - values[i]) ||
            (values[i] < 0 && sum < LLONG_MIN - values[i])) {
            return -1;
        }
        sum += values[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    size_t count;
    size_t i;
    int *values = NULL;
    long long result;
    char trailing;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid list size.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("List is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid list element.\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (scanf(" %c", &trailing) == 1) {
        fputs("Unexpected input.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (add_consecutive(values, count, &result) != 0) {
        fputs("Unable to calculate sum.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}