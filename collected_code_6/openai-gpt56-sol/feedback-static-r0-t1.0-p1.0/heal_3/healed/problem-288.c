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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;
    int valid = 1;

    if (buffer == NULL || size == 0) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && is_space(ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !is_space(ch)) {
        if (length < size - 1) {
            buffer[length++] = (char)ch;
        } else {
            valid = 0;
        }

        ch = getchar();
    }

    buffer[length] = '\0';
    return valid;
}

static int read_uint64(uint64_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-' || buffer[0] == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_size(size_t *value)
{
    uint64_t parsed;

    if (value == NULL || !read_uint64(&parsed) || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static size_t count_self_inverse_elements(const int64_t *array,
                                          size_t length,
                                          uint64_t prime)
{
    size_t count = 0;

    for (size_t i = 0; i < length; ++i) {
        uint64_t residue;

        if (array[i] >= 0) {
            residue = (uint64_t)array[i] % prime;
        } else {
            uint64_t magnitude =
                (uint64_t)(-(array[i] + INT64_C(1))) + UINT64_C(1);
            uint64_t remainder = magnitude % prime;

            residue = remainder == 0 ? UINT64_C(0) : prime - remainder;
        }

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

    if (!read_uint64(&prime) ||
        !read_size(&length) ||
        !is_prime(prime)) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (printf("%zu\n",
               count_self_inverse_elements(array, length, prime)) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}