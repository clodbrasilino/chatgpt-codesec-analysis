#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int multiply_kth_elements(const int64_t *tuples, size_t tuple_count,
                                 size_t tuple_size, size_t k,
                                 int64_t *product)
{
    int64_t result = 1;

    if (tuples == NULL || product == NULL || tuple_count == 0 ||
        tuple_size == 0 || k >= tuple_size) {
        return -1;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        int64_t value = tuples[i * tuple_size + k];

        if (__builtin_mul_overflow(result, value, &result)) {
            return -2;
        }
    }

    *product = result;
    return 0;
}

int main(void)
{
    size_t tuple_count;
    size_t tuple_size;
    size_t k;
    int64_t *tuples = NULL;
    int64_t product;
    int status = EXIT_FAILURE;

    if (scanf("%zu %zu %zu", &tuple_count, &tuple_size, &k) != 3 ||
        tuple_count == 0 || tuple_size == 0 || k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t element_count = tuple_count * tuple_size;

    if (element_count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(element_count * sizeof(*tuples));
    if (tuples == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < element_count; ++i) {
        if (scanf("%" SCNd64, &tuples[i]) != 1) {
            fputs("Invalid tuple data\n", stderr);
            goto cleanup;
        }
    }

    int result = multiply_kth_elements(tuples, tuple_count, tuple_size, k,
                                       &product);
    if (result == -1) {
        fputs("Invalid arguments\n", stderr);
        goto cleanup;
    }

    if (result == -2) {
        fputs("Product overflow\n", stderr);
        goto cleanup;
    }

    printf("%" PRId64 "\n", product);
    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}