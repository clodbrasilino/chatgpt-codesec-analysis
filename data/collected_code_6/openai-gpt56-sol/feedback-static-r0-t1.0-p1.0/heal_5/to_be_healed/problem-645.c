#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int product_at_index(const int64_t *tuples, size_t tuple_count,
                            size_t tuple_size, size_t k, int64_t *result)
{
    if (tuples == NULL || result == NULL || tuple_count == 0 ||
        tuple_size == 0 || k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
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

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[64];
    char *end;
    uintmax_t parsed;

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (value == NULL || scanf("%63s", token) != 1) {
        return -1;
    }

    if (token[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[64];
    char *end;
    intmax_t parsed;

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (value == NULL || scanf("%63s", token) != 1) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    size_t tuple_count;
    size_t tuple_size;
    size_t k;

    if (read_size(&tuple_count) != 0 ||
        read_size(&tuple_size) != 0 ||
        read_size(&k) != 0 ||
        tuple_count == 0 || tuple_size == 0 || k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t element_count = tuple_count * tuple_size;

    if (element_count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *tuples = malloc(element_count * sizeof(*tuples));

    if (tuples == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < element_count; ++i) {
        if (read_int64(&tuples[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    int64_t product;
    int status = product_at_index(tuples, tuple_count, tuple_size, k, &product);

    free(tuples);

    if (status == -2) {
        fputs("Product overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != 0) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", product) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}