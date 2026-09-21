#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (length + 1 >= size) {
            while ((ch = getchar()) != EOF &&
                   !isspace((unsigned char)ch)) {
            }
            return -1;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 1;
}

static int read_size_value(size_t *value)
{
    char buffer[64];
    char *end;
    uintmax_t parsed;
    int result;

    if (value == NULL) {
        return -1;
    }

    result = read_token(buffer, sizeof(buffer));
    if (result != 1 || buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64_value(int64_t *value)
{
    char buffer[64];
    char *end;
    intmax_t parsed;
    int result;

    if (value == NULL) {
        return -1;
    }

    result = read_token(buffer, sizeof(buffer));
    if (result != 1) {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
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
    size_t element_count;
    int64_t *tuples = NULL;
    int64_t product;
    int status = EXIT_FAILURE;

    if (read_size_value(&tuple_count) != 0 ||
        read_size_value(&tuple_size) != 0 ||
        read_size_value(&k) != 0 ||
        tuple_count == 0 || tuple_size == 0 || k >= tuple_size ||
        tuple_count > SIZE_MAX / tuple_size) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    element_count = tuple_count * tuple_size;

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

    switch (multiply_kth_elements(tuples, tuple_count, tuple_size, k,
                                  &product)) {
    case -1:
        fputs("Invalid arguments\n", stderr);
        goto cleanup;
    case -2:
        fputs("Product overflow\n", stderr);
        goto cleanup;
    default:
        break;
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