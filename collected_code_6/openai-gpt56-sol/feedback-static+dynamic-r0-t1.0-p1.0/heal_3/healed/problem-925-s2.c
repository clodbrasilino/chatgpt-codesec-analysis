#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_product(const int64_t *values, size_t count,
                             int64_t *product)
{
    if (values == NULL || product == NULL || count == 0U) {
        return -1;
    }

    int64_t result = 1;

    for (size_t i = 0U; i < count; ++i) {
        const int64_t value = values[i];

        if (value > 0) {
            if (result > INT64_MAX / value ||
                result < INT64_MIN / value) {
                return -1;
            }
        } else if (value < 0) {
            if (value == -1) {
                if (result == INT64_MIN) {
                    return -1;
                }
            } else if (result > INT64_MIN / value ||
                       result < INT64_MAX / value) {
                return -1;
            }
        }

        result *= value;
    }

    *product = result;
    return 0;
}

int main(int argc, char *const argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s number [number ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const size_t count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Input size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        const char *const input = argv[i + 1U];
        char *end = NULL;

        errno = 0;
        const intmax_t parsed = strtoimax(input, &end, 10);

        if (errno == ERANGE || end == input || *end != '\0' ||
            parsed < INT64_MIN || parsed > INT64_MAX) {
            fprintf(stderr, "Invalid number: %s\n", input);
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int64_t)parsed;
    }

    int64_t product = 0;

    if (calculate_product(values, count, &product) != 0) {
        fputs("Unable to calculate product due to invalid input or overflow.\n",
              stderr);
        free(values);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", product);

    free(values);
    return EXIT_SUCCESS;
}