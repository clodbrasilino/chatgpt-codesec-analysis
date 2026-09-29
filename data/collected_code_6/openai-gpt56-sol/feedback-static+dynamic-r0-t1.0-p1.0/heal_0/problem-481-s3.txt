#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

static bool subset_sum(const int *values, size_t count, int target, bool *result)
{
    int64_t min_sum = 0;
    int64_t max_sum = 0;

    if (result == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    *result = false;

    for (size_t i = 0; i < count; ++i) {
        if (values[i] < 0) {
            min_sum += values[i];
        } else {
            max_sum += values[i];
        }
    }

    if ((int64_t)target < min_sum || (int64_t)target > max_sum) {
        return true;
    }

    uint64_t range = (uint64_t)(max_sum - min_sum) + 1U;

    if (range > SIZE_MAX || (size_t)range > SIZE_MAX / sizeof(bool)) {
        return false;
    }

    bool *reachable = calloc((size_t)range, sizeof(*reachable));
    if (reachable == NULL) {
        return false;
    }

    reachable[(size_t)(-min_sum)] = true;

    if (target >= 0) {
        for (size_t i = 0; i < count; ++i) {
            if (values[i] >= 0) {
                size_t shift = (size_t)values[i];
                for (size_t j = (size_t)range; j-- > shift;) {
                    if (reachable[j - shift]) {
                        reachable[j] = true;
                    }
                }
            } else {
                size_t shift = (size_t)(-(int64_t)values[i]);
                for (size_t j = 0; j + shift < (size_t)range; ++j) {
                    if (reachable[j + shift]) {
                        reachable[j] = true;
                    }
                }
            }
        }
    } else {
        for (size_t i = 0; i < count; ++i) {
            if (values[i] >= 0) {
                size_t shift = (size_t)values[i];
                for (size_t j = (size_t)range; j-- > shift;) {
                    if (reachable[j - shift]) {
                        reachable[j] = true;
                    }
                }
            } else {
                size_t shift = (size_t)(-(int64_t)values[i]);
                for (size_t j = 0; j + shift < (size_t)range; ++j) {
                    if (reachable[j + shift]) {
                        reachable[j] = true;
                    }
                }
            }
        }
    }

    *result = reachable[(size_t)((int64_t)target - min_sum)];
    free(reachable);
    return true;
}

int main(void)
{
    size_t count;
    int target;

    if (scanf("%zu %d", &count, &target) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    bool found;
    if (!subset_sum(values, count, target, &found)) {
        fputs("Unable to determine subset sum\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    puts(found ? "Yes" : "No");
    free(values);
    return EXIT_SUCCESS;
}