#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

static int saturating_add(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || b > UINT64_MAX - a) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int saturating_mul2_add1(uint64_t value, uint64_t *result)
{
    if (result == NULL || value > (UINT64_MAX - 1) / 2) {
        return 0;
    }

    *result = value * 2 + 1;
    return 1;
}

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;
    int truncated = 0;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length < size - 1) {
            buffer[length++] = (char)ch;
        } else {
            truncated = 1;
        }

        ch = fgetc(stdin);
    }

    buffer[length] = '\0';

    if (ferror(stdin) || truncated) {
        return 0;
    }

    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int count_subsequences(const uint64_t *array, size_t length,
                              uint64_t k, uint64_t *result)
{
    uint64_t *products = NULL;
    uint64_t count = 0;
    size_t capacity;
    size_t used = 1;

    if (result == NULL || (array == NULL && length != 0)) {
        return 0;
    }

    *result = 0;

    if (length == 0 || k == 0) {
        return 1;
    }

    if (length == SIZE_MAX) {
        return 0;
    }

    capacity = length + 1;

    if (capacity > SIZE_MAX / sizeof(*products)) {
        return 0;
    }

    products = malloc(capacity * sizeof(*products));
    if (products == NULL) {
        return 0;
    }

    products[0] = 1;

    for (size_t index = 0; index < length; ++index) {
        uint64_t value = array[index];

        if (value == 0) {
            if (!saturating_mul2_add1(count, &count)) {
                free(products);
                return 0;
            }
            continue;
        }

        if (value >= k) {
            continue;
        }

        size_t new_count = 0;
        uint64_t limit = (k - 1) / value;

        for (size_t position = 0; position < used; ++position) {
            if (products[position] <= limit) {
                if (new_count >= capacity) {
                    free(products);
                    return 0;
                }

                products[new_count++] = products[position] * value;
            }
        }

        if (new_count > UINT64_MAX ||
            !saturating_add(count, (uint64_t)new_count, &count)) {
            free(products);
            return 0;
        }

        if (new_count != 0) {
            if (new_count > capacity - used ||
                used > SIZE_MAX / sizeof(*products)) {
                free(products);
                return 0;
            }

            memmove(products + new_count, products,
                    used * sizeof(*products));
            used += new_count;
        }
    }

    free(products);
    *result = count;
    return 1;
}

int main(void)
{
    char *token = NULL;
    const size_t token_size = 128;
    size_t length;
    uint64_t k;
    uint64_t *array = NULL;
    uint64_t result;
    int status = EXIT_FAILURE;

    token = malloc(token_size);
    if (token == NULL) {
        goto cleanup;
    }

    if (!read_token(token, token_size) ||
        !parse_size(token, &length) ||
        !read_token(token, token_size) ||
        !parse_uint64(token, &k)) {
        goto cleanup;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        goto cleanup;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            goto cleanup;
        }
    }

    for (size_t index = 0; index < length; ++index) {
        if (!read_token(token, token_size) ||
            !parse_uint64(token, &array[index])) {
            goto cleanup;
        }
    }

    if (!count_subsequences(array, length, k, &result)) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(array);
    free(token);
    return status;
}