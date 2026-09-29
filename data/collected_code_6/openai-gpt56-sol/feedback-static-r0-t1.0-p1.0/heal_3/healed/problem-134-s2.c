#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

typedef enum {
    PARITY_ERROR = -1,
    PARITY_EVEN = 0,
    PARITY_ODD = 1
} Parity;

static int read_token(char **buffer)
{
    char *token;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    token = malloc(capacity);
    if (token == NULL) {
        return 0;
    }

    do {
        if (length == capacity - 1) {
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
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    token[length] = '\0';
    *buffer = token;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '-') {
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
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '-') {
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
    char *buffer;
    char *end;
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

static Parity last_element_parity_after_operations(
    const int64_t array[],
    size_t length,
    uint64_t p)
{
    if (array == NULL || length == 0) {
        return PARITY_ERROR;
    }

    if (p == 0) {
        return array[length - 1] % INT64_C(2) != 0
                   ? PARITY_ODD
                   : PARITY_EVEN;
    }

    return PARITY_EVEN;
}

int main(void)
{
    size_t length;
    uint64_t p;
    int64_t last = 0;
    Parity result;

    if (!read_size(&length) || !read_uint64(&p) || length == 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&last)) {
            return EXIT_FAILURE;
        }
    }

    result = last_element_parity_after_operations(&last, 1, p);
    if (result == PARITY_ERROR) {
        return EXIT_FAILURE;
    }

    if (puts(result == PARITY_EVEN ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}