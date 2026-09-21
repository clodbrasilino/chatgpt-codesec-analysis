#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

static bool has_subset_sum(const int *values, size_t count, size_t target)
{
    if (target == 0U) {
        return true;
    }

    if (values == NULL || target == SIZE_MAX) {
        return false;
    }

    bool *reachable = calloc(target + 1U, sizeof(*reachable));
    if (reachable == NULL) {
        return false;
    }

    reachable[0] = true;

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] < 0) {
            free(reachable);
            return false;
        }

        size_t value = (size_t)values[i];
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
            free(reachable);
            return true;
        }
    }

    bool result = reachable[target];
    free(reachable);
    return result;
}

static bool read_size(const char *prompt, size_t *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end = NULL;

    if (prompt == NULL || result == NULL) {
        return false;
    }

    fputs(prompt, stdout);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }

    errno = 0;
    unsigned long long value = strtoull(buffer, &end, 10);

    if (errno != 0 || end == buffer) {
        return false;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
        ++end;
    }

    if (*end != '\0' || value > SIZE_MAX) {
        return false;
    }

    *result = (size_t)value;
    return true;
}

int main(void)
{
    size_t count = 0U;
    size_t target = 0U;

    if (!read_size("Enter the number of elements: ", &count)) {
        fputs("Invalid element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fputs("Element count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = NULL;
    if (count > 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    fputs("Enter the nonnegative elements: ", stdout);
    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1 || values[i] < 0) {
            fputs("Invalid element.\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%*[\n]") == EOF && ferror(stdin)) {
        fputs("Input error.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (!read_size("Enter the target sum: ", &target)) {
        fputs("Invalid target sum.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    bool found = has_subset_sum(values, count, target);
    puts(found ? "A subset with the target sum exists."
               : "No subset with the target sum exists.");

    free(values);
    return EXIT_SUCCESS;
}