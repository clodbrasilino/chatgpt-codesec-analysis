#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

typedef enum {
    PARITY_EVEN = 0,
    PARITY_ODD = 1
} Parity;

static Parity last_element_parity_after_operations(int64_t last, uint64_t p)
{
    return p != UINT64_C(0)
        ? PARITY_EVEN
        : (((uint64_t)last & UINT64_C(1)) != 0U ? PARITY_ODD : PARITY_EVEN);
}

static int discard_token(int ch)
{
    while (ch != EOF && !isspace((unsigned char)ch)) {
        ch = getchar();
    }

    return ch == EOF && ferror(stdin) ? 0 : 1;
}

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= capacity - 1U) {
            buffer[0] = '\0';
            discard_token(ch);
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    if (ch == EOF && ferror(stdin)) {
        buffer[0] = '\0';
        return 0;
    }

    buffer[length] = '\0';
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char token[sizeof("-18446744073709551615")];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(token, sizeof token) ||
        token[0] == '-' || token[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
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
    char token[sizeof("-9223372036854775808")];
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    size_t length;
    uint64_t p;
    int64_t last = 0;
    Parity result;

    if (!read_size(&length) || !read_uint64(&p) || length == 0U) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!read_int64(&last)) {
            return EXIT_FAILURE;
        }
    }

    result = last_element_parity_after_operations(last, p);

    if (printf("%s\n", result == PARITY_EVEN ? "Even" : "Odd") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}