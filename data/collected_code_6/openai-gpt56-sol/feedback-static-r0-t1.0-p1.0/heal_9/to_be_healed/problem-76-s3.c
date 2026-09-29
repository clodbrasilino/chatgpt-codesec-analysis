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

    count = s * (s + 1) *
            (3 * (__uint128_t)larger - s + 1) / 6;

    if (count > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)count;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t number;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
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

static int read_token(char *buffer, size_t capacity, int *delimiter)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || capacity < 2 || delimiter == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    do {
        if (length + 1 >= capacity) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != EOF &&
                   !isspace((unsigned char)ch)) {
            }
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    *delimiter = ch;
    return 1;
}

static int parse_input(uint64_t *width, uint64_t *height)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[32];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[32];
    int delimiter;
    int ch;

    if (width == NULL || height == NULL) {
        return 0;
    }

    if (!read_token(first, sizeof first, &delimiter)) {
        return 0;
    }

    if (delimiter == EOF ||
        !read_token(second, sizeof second, &delimiter)) {
        return 0;
    }

    if (!parse_uint64(first, width) ||
        !parse_uint64(second, height)) {
        return 0;
    }

    ch = delimiter;
    while (ch != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
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