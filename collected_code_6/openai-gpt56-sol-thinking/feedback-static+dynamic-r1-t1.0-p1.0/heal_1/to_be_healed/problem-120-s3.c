#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static bool multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return false;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && b < INT64_MAX / a)) {
            return false;
        }
    }

    *result = a * b;
    return true;
}

bool find_maximum_tuple_product(const Tuple *tuples, size_t count,
                                int64_t *maximum_product)
{
    int64_t maximum = INT64_MIN;

    if (tuples == NULL || maximum_product == NULL || count == 0) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t product;

        if (!multiply_checked(tuples[i].first, tuples[i].second, &product)) {
            return false;
        }

        if (product > maximum) {
            maximum = product;
        }
    }

    *maximum_product = maximum;
    return true;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    int64_t maximum_product;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fprintf(stderr, "Invalid tuple count\n");
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64 " %" SCNd64,
                  &tuples[i].first, &tuples[i].second) != 2) {
            fprintf(stderr, "Invalid tuple input\n");
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_maximum_tuple_product(tuples, count, &maximum_product)) {
        fprintf(stderr, "Unable to calculate maximum product\n");
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", maximum_product);

    free(tuples);
    return EXIT_SUCCESS;
}