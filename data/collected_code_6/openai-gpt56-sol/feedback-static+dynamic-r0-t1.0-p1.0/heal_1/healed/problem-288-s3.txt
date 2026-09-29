#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_token(char *buffer, size_t size)
{
    int c;
    size_t length = 0;

    do {
        c = getchar();
    } while (c != EOF && (c == ' ' || c == '\t' || c == '\n' ||
                          c == '\r' || c == '\f' || c == '\v'));

    if (c == EOF) {
        return 0;
    }

    while (c != EOF && c != ' ' && c != '\t' && c != '\n' &&
           c != '\r' && c != '\f' && c != '\v') {
        if (length + 1U >= size) {
            do {
                c = getchar();
            } while (c != EOF && c != ' ' && c != '\t' && c != '\n' &&
                     c != '\r' && c != '\f' && c != '\v');
            return 0;
        }

        buffer[length++] = (char)c;
        c = getchar();
    }

    buffer[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text[0] == '\0' || text[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
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
    char *end;
    uintmax_t parsed;

    if (text[0] == '\0' || text[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text[0] == '\0') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int is_prime(uint64_t p)
{
    uint64_t divisor;

    if (p < UINT64_C(2)) {
        return 0;
    }

    if (p % UINT64_C(2) == 0U) {
        return p == UINT64_C(2);
    }

    for (divisor = UINT64_C(3);
         divisor <= p / divisor;
         divisor += UINT64_C(2)) {
        if (p % divisor == 0U) {
            return 0;
        }
    }

    return 1;
}

static size_t count_self_inverse_elements(const int64_t array[],
                                          size_t length,
                                          uint64_t p)
{
    size_t count = 0;
    size_t i;

    for (i = 0; i < length; ++i) {
        uint64_t residue;

        if (array[i] >= 0) {
            residue = (uint64_t)array[i] % p;
        } else {
            uint64_t magnitude = (uint64_t)(-(array[i] + 1)) + UINT64_C(1);
            uint64_t remainder = magnitude % p;
            residue = remainder == 0U ? 0U : p - remainder;
        }

        if (residue == UINT64_C(1) || residue == p - UINT64_C(1)) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char token[128];
    size_t length;
    uint64_t p;
    int64_t *array = NULL;
    size_t i;
    size_t count;

    if (!read_token(token, sizeof token) || !parse_size(token, &length) ||
        !read_token(token, sizeof token) || !parse_uint64(token, &p)) {
        return EXIT_FAILURE;
    }

    if (!is_prime(p) || length > SIZE_MAX / sizeof *array) {
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        array = malloc(length * sizeof *array);
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < length; ++i) {
        if (!read_token(token, sizeof token) || !parse_int64(token, &array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    count = count_self_inverse_elements(array, length, p);

    if (printf("%zu\n", count) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}