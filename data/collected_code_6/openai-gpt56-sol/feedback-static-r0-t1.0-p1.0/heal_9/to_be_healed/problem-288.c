#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int is_prime(uint64_t n)
{
    if (n < UINT64_C(2)) {
        return 0;
    }

    if (n % UINT64_C(2) == 0) {
        return n == UINT64_C(2);
    }

    for (uint64_t divisor = UINT64_C(3);
         divisor <= n / divisor;
         divisor += UINT64_C(2)) {
        if (n % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

static int read_token(char **token)
{
    enum { INITIAL_CAPACITY = 32 };
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = INITIAL_CAPACITY;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && is_space(ch));

    if (ch == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !is_space(ch)) {
        if (length > SIZE_MAX - 2) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            if (new_capacity < capacity || new_capacity < required) {
                free(buffer);
                return 0;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed <= UINT64_MAX;

    if (valid) {
        *value = (uint64_t)parsed;
    }

    free(buffer);
    return valid;
}

static int read_size(size_t *value)
{
    uint64_t parsed;

    if (value == NULL ||
        !read_uint64(&parsed) ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed >= INT64_MIN &&
            parsed <= INT64_MAX;

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(buffer);
    return valid;
}

static uint64_t modulo_int64(int64_t value, uint64_t modulus)
{
    uint64_t magnitude;
    uint64_t remainder;

    if (value >= 0) {
        return (uint64_t)value % modulus;
    }

    magnitude = (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
    remainder = magnitude % modulus;

    return remainder == 0 ? UINT64_C(0) : modulus - remainder;
}

static size_t count_self_inverse_elements(const int64_t *array,
                                          size_t length,
                                          uint64_t prime)
{
    size_t count = 0;

    for (size_t i = 0; i < length; ++i) {
        uint64_t residue = modulo_int64(array[i], prime);

        if (residue == UINT64_C(1) ||
            residue == prime - UINT64_C(1)) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    uint64_t prime;
    size_t length;
    int64_t *array = NULL;
    int status = EXIT_FAILURE;

    if (!read_uint64(&prime) ||
        !read_size(&length) ||
        !is_prime(prime)) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            goto cleanup;
        }
    }

    if (printf("%zu\n",
               count_self_inverse_elements(array, length, prime)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(array);
    return status;
}