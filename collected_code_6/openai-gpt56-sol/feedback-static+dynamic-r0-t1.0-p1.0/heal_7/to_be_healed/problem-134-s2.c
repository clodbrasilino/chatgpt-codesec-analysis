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

enum {
    TOKEN_CAPACITY = 64
};

static Parity last_element_parity_after_operations(int64_t last, uint64_t p)
{
    if (p != UINT64_C(0)) {
        return PARITY_EVEN;
    }

    return ((uint64_t)last & UINT64_C(1)) != UINT64_C(0)
        ? PARITY_ODD
        : PARITY_EVEN;
}

static int discard_token(int ch)
{
    while (ch != EOF && !isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return ch != EOF || !ferror(stdin);
}

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    buffer[0] = '\0';

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1U >= capacity) {
            (void)discard_token(ch);
            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[TOKEN_CAPACITY];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(token, sizeof token)) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || end == NULL || *end != '\0' ||
        parsed > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_size(size_t *value)
{
    uint64_t parsed;

    if (value == NULL || !read_uint64(&parsed)) {
        return 0;
    }

#if SIZE_MAX < UINT64_MAX
    if (parsed > (uint64_t)SIZE_MAX) {
        return 0;
    }
#endif

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[TOKEN_CAPACITY];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof token)) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || end == NULL || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    size_t length;
    uint64_t p;
    int64_t last = INT64_C(0);
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

    if (fputs(result == PARITY_EVEN ? "Even\n" : "Odd\n", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}