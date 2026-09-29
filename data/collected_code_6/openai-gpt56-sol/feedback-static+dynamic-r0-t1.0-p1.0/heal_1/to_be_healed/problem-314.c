#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int64_t max_value(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

static int64_t maximum_non_adjacent_sum(const int64_t *top,
                                        const int64_t *bottom,
                                        size_t n)
{
    int64_t exclude_previous = 0;
    int64_t include_previous = 0;

    for (size_t i = 0; i < n; ++i) {
        int64_t column_value = max_value(top[i], bottom[i]);
        int64_t include_current = exclude_previous + column_value;
        int64_t exclude_current =
            max_value(exclude_previous, include_previous);

        if (include_current < 0) {
            include_current = 0;
        }

        include_previous = include_current;
        exclude_previous = exclude_current;
    }

    return max_value(include_previous, exclude_previous);
}

int main(void)
{
    size_t n;

    if (scanf("%zu", &n) != 1 || n == 0 ||
        n > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *top = malloc(n * sizeof(*top));
    int64_t *bottom = malloc(n * sizeof(*bottom));

    if (top == NULL || bottom == NULL) {
        free(top);
        free(bottom);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &top[i]) != 1) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &bottom[i]) != 1) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    int64_t result = maximum_non_adjacent_sum(top, bottom, n);
    printf("%" PRId64 "\n", result);

    free(top);
    free(bottom);
    return EXIT_SUCCESS;
}