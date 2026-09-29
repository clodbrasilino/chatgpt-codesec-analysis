#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm(uintmax_t a, uintmax_t b, uintmax_t *result)
{
    uintmax_t quotient;

    if (a == 0 || b == 0 || result == NULL) {
        return -1;
    }

    quotient = a / gcd(a, b);

    if (quotient > UINTMAX_MAX / b) {
        return -1;
    }

    *result = quotient * b;
    return 0;
}

static int parse_uintmax(const char **input, uintmax_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    start = *input;

    if (*start == '\0' || *start == '+' || *start == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        return -1;
    }

    *input = end;
    *value = parsed;
    return 0;
}

static int read_line(FILE *stream, char **buffer)
{
    size_t capacity = 64;
    size_t length = 0;
    char *data;

    if (stream == NULL || buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    data = malloc(capacity);

    if (data == NULL) {
        return -2;
    }

    for (;;) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(data);
                return -3;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(data);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(data, new_capacity);

            if (resized == NULL) {
                free(data);
                return -2;
            }

            data = resized;
            capacity = new_capacity;
        }

        data[length++] = (char)ch;
    }

    data[length] = '\0';
    *buffer = data;
    return 0;
}

int main(void)
{
    char *input = NULL;
    const char *cursor;
    uintmax_t a;
    uintmax_t b;
    uintmax_t result;
    int status;

    status = read_line(stdin, &input);

    if (status != 0) {
        if (status == -2) {
            fputs("Memory allocation failed\n", stderr);
        } else if (status == -3) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Invalid input\n", stderr);
        }

        return EXIT_FAILURE;
    }

    cursor = input;

    if (parse_uintmax(&cursor, &a) != 0 ||
        parse_uintmax(&cursor, &b) != 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || a == 0 || b == 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (lcm(a, b, &result) != 0) {
        free(input);
        fputs("LCM cannot be represented\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}