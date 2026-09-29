#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

static int read_token(char **token)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
    int ch;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    do {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size(size_t *value)
{
    char *token;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    if (token[0] == '-') {
        free(token);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        free(token);
        return -1;
    }

    *value = (size_t)parsed;
    free(token);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *token;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(&token) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return -1;
    }

    *value = (int64_t)parsed;
    free(token);
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