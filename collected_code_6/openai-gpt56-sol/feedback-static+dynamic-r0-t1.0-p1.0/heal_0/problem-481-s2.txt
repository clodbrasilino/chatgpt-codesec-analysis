#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

static bool add_overflows_size_t(size_t a, size_t b)
{
    return a > SIZE_MAX - b;
}

static bool subset_sum(const size_t *values, size_t count, size_t target, bool *result)
{
    bool *reachable = NULL;
    size_t table_size;

    if (result == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    *result = false;

    if (add_overflows_size_t(target, 1U)) {
        return false;
    }

    table_size = target + 1U;
    reachable = calloc(table_size, sizeof(*reachable));
    if (reachable == NULL) {
        return false;
    }

    reachable[0] = true;

    for (size_t i = 0U; i < count; ++i) {
        const size_t value = values[i];

        if (value > target) {
            continue;
        }

        for (size_t sum = target; sum >= value; --sum) {
            if (reachable[sum - value]) {
                reachable[sum] = true;
            }

            if (sum == value) {
                break;
            }
        }

        if (reachable[target]) {
            *result = true;
            free(reachable);
            return true;
        }
    }

    *result = reachable[target];
    free(reachable);
    return true;
}

int main(void)
{
    size_t count;
    size_t target;
    size_t *values = NULL;
    bool found;

    if (scanf("%zu %zu", &count, &target) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Input size is too large\n");
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%zu", &values[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!subset_sum(values, count, target, &found)) {
        fprintf(stderr, "Unable to compute subset sum\n");
        free(values);
        return EXIT_FAILURE;
    }

    puts(found ? "Yes" : "No");

    free(values);
    return EXIT_SUCCESS;
}