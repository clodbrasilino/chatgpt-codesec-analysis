#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int product_at_index(const int64_t *tuples, size_t tuple_count,
                            size_t tuple_size, size_t k, int64_t *result)
{
    if (tuples == NULL || result == NULL || tuple_count == 0 ||
        tuple_size == 0 || k >= tuple_size) {
        return -1;
    }

    int64_t product = 1;

    for (size_t i = 0; i < tuple_count; ++i) {
        int64_t value = tuples[i * tuple_size + k];

        if (__builtin_mul_overflow(product, value, &product)) {
            return -2;
        }
    }

    *result = product;
    return 0;
}

int main(void)
{
    size_t tuple_count;
    size_t tuple_size;
    size_t k;

    if (scanf("%zu %zu %zu", &tuple_count, &tuple_size, &k) != 3 ||
        tuple_count == 0 || tuple_size == 0 || k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size ||
        tuple_count * tuple_size > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t element_count = tuple_count * tuple_size;
    int64_t *tuples = malloc(element_count * sizeof(*tuples));

    if (tuples == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < element_count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &tuples[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int64_t product;
    int status = product_at_index(
        tuples, tuple_count, tuple_size, k, &product
    );

    free(tuples);

    if (status == -2) {
        fputs("Product overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != 0) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", product);
    return EXIT_SUCCESS;
}