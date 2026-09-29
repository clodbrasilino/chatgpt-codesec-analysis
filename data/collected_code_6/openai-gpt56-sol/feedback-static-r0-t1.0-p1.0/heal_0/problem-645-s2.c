#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int product_at_index(const long long *const *tuples,
                            const size_t *tuple_lengths,
                            size_t tuple_count,
                            size_t k,
                            long long *result)
{
    size_t i;
    long long product = 1;

    if (tuples == NULL || tuple_lengths == NULL || result == NULL || tuple_count == 0) {
        return 0;
    }

    for (i = 0; i < tuple_count; ++i) {
        long long value;

        if (tuples[i] == NULL || k >= tuple_lengths[i]) {
            return 0;
        }

        value = tuples[i][k];

        if (value > 0) {
            if (product > 0) {
                if (product > LLONG_MAX / value) {
                    return 0;
                }
            } else if (product < LLONG_MIN / value) {
                return 0;
            }
        } else if (value < 0) {
            if (product > 0) {
                if (value < LLONG_MIN / product) {
                    return 0;
                }
            } else if (product != 0 && value < LLONG_MAX / product) {
                return 0;
            }
        }

        product *= value;
    }

    *result = product;
    return 1;
}

static int read_size(const char *prompt, size_t *value)
{
    unsigned long long input;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (printf("%s", prompt) < 0 || fflush(stdout) != 0) {
        return 0;
    }

    if (scanf("%llu", &input) != 1 || input > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)input;
    return 1;
}

int main(void)
{
    long long **tuples = NULL;
    size_t *lengths = NULL;
    size_t tuple_count;
    size_t tuple_length;
    size_t k;
    size_t i;
    size_t j;
    long long result;
    int status = EXIT_FAILURE;

    if (!read_size("Number of tuples: ", &tuple_count) ||
        !read_size("Length of each tuple: ", &tuple_length) ||
        !read_size("Index k: ", &k) ||
        tuple_count == 0 ||
        tuple_length == 0 ||
        k >= tuple_length ||
        tuple_count > SIZE_MAX / sizeof(*tuples) ||
        tuple_count > SIZE_MAX / sizeof(*lengths) ||
        tuple_length > SIZE_MAX / sizeof(**tuples)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = calloc(tuple_count, sizeof(*tuples));
    lengths = malloc(tuple_count * sizeof(*lengths));

    if (tuples == NULL || lengths == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        goto cleanup;
    }

    for (i = 0; i < tuple_count; ++i) {
        tuples[i] = malloc(tuple_length * sizeof(**tuples));
        if (tuples[i] == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            goto cleanup;
        }

        lengths[i] = tuple_length;

        for (j = 0; j < tuple_length; ++j) {
            if (scanf("%lld", &tuples[i][j]) != 1) {
                fputs("Invalid tuple value.\n", stderr);
                goto cleanup;
            }
        }
    }

    if (!product_at_index((const long long *const *)tuples,
                          lengths,
                          tuple_count,
                          k,
                          &result)) {
        fputs("Unable to calculate product.\n", stderr);
        goto cleanup;
    }

    if (printf("%lld\n", result) < 0) {
        fputs("Output error.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    if (tuples != NULL) {
        for (i = 0; i < tuple_count; ++i) {
            free(tuples[i]);
        }
    }

    free(tuples);
    free(lengths);
    return status;
}