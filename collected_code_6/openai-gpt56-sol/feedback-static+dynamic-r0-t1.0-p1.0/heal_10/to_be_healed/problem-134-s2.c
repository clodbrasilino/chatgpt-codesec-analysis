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
    if (p != UINT64_C(0)) {
        return PARITY_EVEN;
    }

    return (((uint64_t)last & UINT64_C(1)) != UINT64_C(0))
        ? PARITY_ODD
        : PARITY_EVEN;
}

static int read_token(char **token)
{
    size_t capacity = 32U;
    size_t length = 0U;
    char *buffer;
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
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
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
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)UINT64_MAX) {
        free(token);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(token);
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
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        free(token);
        return 0;
    }

    *value = (int64_t)parsed;
    free(token);
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