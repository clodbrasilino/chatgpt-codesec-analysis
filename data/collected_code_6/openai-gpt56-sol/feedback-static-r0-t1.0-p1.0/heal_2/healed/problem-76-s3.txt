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

static int parse_dimensions(const char *input, uint64_t *width,
                            uint64_t *height)
{
    const char *p;
    char *end;
    uintmax_t value;

    if (input == NULL || width == NULL || height == NULL) {
        return 0;
    }

    p = input;

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0' || *p == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(p, &end, 10);
    if (errno == ERANGE || end == p || value > UINT64_MAX) {
        return 0;
    }
    *width = (uint64_t)value;

    p = end;
    if (!isspace((unsigned char)*p)) {
        return 0;
    }

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0' || *p == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(p, &end, 10);
    if (errno == ERANGE || end == p || value > UINT64_MAX) {
        return 0;
    }
    *height = (uint64_t)value;

    p = end;
    while (isspace((unsigned char)*p)) {
        ++p;
    }

    return *p == '\0';
}

static int read_line(char *buffer, size_t size)
{
    int ch;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    if (fgets(buffer, size, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') != NULL || feof(stdin)) {
        return 1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return 0;
}

int main(void)
{
    char input[256];
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (!read_line(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_dimensions(input, &width, &height)) {
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