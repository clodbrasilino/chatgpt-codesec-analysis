#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t smaller;
    uint64_t larger;
    __uint128_t s;
    __uint128_t count;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    smaller = width < height ? width : height;
    larger = width < height ? height : width;
    s = smaller;

    count = s * (s + 1) *
            (3 * (__uint128_t)larger - s + 1) / 6;

    if (count > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)count;
    return 1;
}

static int read_token(char **token, int *delimiter)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int ch;

    if (token == NULL || delimiter == NULL) {
        return 0;
    }

    *token = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        free(buffer);
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return 0;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    *delimiter = ch;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t number;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    number = strtoumax(text, &end, 10);

    if (errno == ERANGE || number > UINT64_MAX ||
        end == text || *end != '\0') {
        return 0;
    }

    *value = (uint64_t)number;
    return 1;
}

static int parse_input(uint64_t *width, uint64_t *height)
{
    char *first = NULL;
    char *second = NULL;
    int delimiter;
    int ch;
    int valid = 0;

    if (width == NULL || height == NULL) {
        return 0;
    }

    if (!read_token(&first, &delimiter) || delimiter == EOF) {
        goto cleanup;
    }

    if (!read_token(&second, &delimiter)) {
        goto cleanup;
    }

    if (!parse_uint64(first, width) ||
        !parse_uint64(second, height)) {
        goto cleanup;
    }

    ch = delimiter;
    while (ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            goto cleanup;
        }
        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    valid = 1;

cleanup:
    free(first);
    free(second);
    return valid;
}

int main(void)
{
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (!parse_input(&width, &height)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or result overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}