#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

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

    count = s * (s + 1) * (3 * (__uint128_t)larger - s + 1) / 6;

    if (count > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)count;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (length + 1 >= capacity) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';

    if (ch == EOF && ferror(stdin)) {
        return 0;
    }

    return 1;
}

static int parse_input(uint64_t *width, uint64_t *height)
{
    char first[32];
    char second[32];
    int ch;

    if (width == NULL || height == NULL) {
        return 0;
    }

    if (!read_token(first, sizeof first) ||
        !read_token(second, sizeof second)) {
        return 0;
    }

    if (!parse_uint64(first, width) ||
        !parse_uint64(second, height)) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
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