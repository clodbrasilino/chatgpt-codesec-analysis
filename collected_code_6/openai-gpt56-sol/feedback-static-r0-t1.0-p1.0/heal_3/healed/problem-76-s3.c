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

    count = s * (s + 1) * (3 * (__uint128_t)larger - s + 1) / 6;

    if (count > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)count;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(NULL, &end, 10);

    if (errno == ERANGE || end == NULL || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int parse_input(uint64_t *width, uint64_t *height)
{
    int ch;
    char token[UINT64_MAX == UINTMAX_MAX ? 32 : 64];
    size_t length = 0;
    unsigned int field = 0;
    uint64_t values[2];

    if (width == NULL || height == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (isspace((unsigned char)ch)) {
            if (length == 0) {
                continue;
            }

            if (field >= 2) {
                return 0;
            }

            token[length] = '\0';

            {
                char *end;
                uintmax_t parsed;

                errno = 0;
                parsed = strtoumax(token, &end, 10);
                if (errno == ERANGE || end == token || *end != '\0' ||
                    parsed > UINT64_MAX) {
                    return 0;
                }

                values[field++] = (uint64_t)parsed;
            }

            length = 0;
            continue;
        }

        if (field >= 2 || length + 1 >= sizeof token) {
            return 0;
        }

        token[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        return 0;
    }

    if (length != 0) {
        if (field >= 2) {
            return 0;
        }

        token[length] = '\0';

        {
            char *end;
            uintmax_t parsed;

            errno = 0;
            parsed = strtoumax(token, &end, 10);
            if (errno == ERANGE || end == token || *end != '\0' ||
                parsed > UINT64_MAX) {
                return 0;
            }

            values[field++] = (uint64_t)parsed;
        }
    }

    if (field != 2) {
        return 0;
    }

    *width = values[0];
    *height = values[1];
    return 1;
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

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}