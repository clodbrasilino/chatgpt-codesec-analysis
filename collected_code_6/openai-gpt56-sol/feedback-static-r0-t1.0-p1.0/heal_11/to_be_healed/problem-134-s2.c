#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

typedef enum {
    PARITY_EVEN,
    PARITY_ODD
} Parity;

static int read_token(char **buffer)
{
    size_t length = 0;
    size_t capacity = 32;
    char *token;
    int ch;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    token = malloc(capacity);
    if (token == NULL) {
        return 0;
    }

    for (;;) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(token);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(token, new_capacity);
            if (resized == NULL) {
                free(token);
                return 0;
            }

            token = resized;
            capacity = new_capacity;
        }

        token[length++] = (char)ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF || isspace((unsigned char)ch)) {
            break;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        free(token);
        return 0;
    }

    token[length] = '\0';
    *buffer = token;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > UINT64_MAX) {
        free(buffer);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(buffer);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static Parity last_element_parity_after_operations(int64_t last, uint64_t p)
{
    if (p != 0) {
        return PARITY_EVEN;
    }

    return last % INT64_C(2) == 0 ? PARITY_EVEN : PARITY_ODD;
}

int main(void)
{
    size_t length;
    uint64_t p;
    int64_t last = 0;
    Parity result;

    if (!read_size(&length) || length == 0 || !read_uint64(&p)) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&last)) {
            return EXIT_FAILURE;
        }
    }

    result = last_element_parity_after_operations(last, p);

    if (puts(result == PARITY_EVEN ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}