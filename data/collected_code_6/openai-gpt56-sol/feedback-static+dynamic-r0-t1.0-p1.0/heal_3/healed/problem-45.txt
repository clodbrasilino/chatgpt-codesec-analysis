#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGTH 128

static uint64_t magnitude(int64_t value)
{
    if (value >= 0) {
        return (uint64_t)value;
    }

    return (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
}

static uint64_t gcd_pair(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1 >= capacity) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));

            return -1;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
        return -1;
    }

    buffer[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    char token[MAX_TOKEN_LENGTH];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(token, sizeof token) != 0) {
        return -1;
    }

    if (token[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    char token[MAX_TOKEN_LENGTH];
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(token, sizeof token) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count;
    uint64_t result = 0;

    if (read_size(&count) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t value;

        if (read_int64(&value) != 0) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        result = gcd_pair(result, magnitude(value));
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}