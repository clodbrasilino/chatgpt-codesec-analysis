#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_size_t_value(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    uintmax_t parsed;

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (value == NULL || scanf("%127s", token) != 1) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        token[0] == '-' || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64_value(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[128];
    char *end;
    intmax_t parsed;

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (value == NULL || scanf("%127s", token) != 1) {
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

static int multiply_kth_elements(const int64_t *tuples, size_t tuple_count,
                                 size_t tuple_size, size_t k,
                                 int64_t *product)
{
    int64_t result = 1;

    if (tuples == NULL || product == NULL || tuple_count == 0 ||
        tuple_size == 0 || k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
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

    if (read_size_t_value(&tuple_count) != 0 ||
        read_size_t_value(&tuple_size) != 0 ||
        read_size_t_value(&k) != 0 ||
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
        if (read_int64_value(&tuples[i]) != 0) {
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

    if (printf("%" PRId64 "\n", product) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}