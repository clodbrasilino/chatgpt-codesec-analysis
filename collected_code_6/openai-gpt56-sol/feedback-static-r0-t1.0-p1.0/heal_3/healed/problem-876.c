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
    uintmax_t divisor;

    if (a == 0 || b == 0 || result == NULL) {
        return -1;
    }

    divisor = gcd(a, b);

    if (a / divisor > UINTMAX_MAX / b) {
        return -1;
    }

    *result = (a / divisor) * b;
    return 0;
}

static int parse_uintmax(const char **input, uintmax_t *value)
{
    const char *start;
    char *end;

    if (input == NULL || *input == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    start = *input;

    if (*start == '\0' || *start == '-' || *start == '+') {
        return -1;
    }

    errno = 0;
    *value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        return -1;
    }

    *input = end;
    return 0;
}

static int read_line(FILE *stream, char **buffer)
{
    size_t capacity = 64;
    size_t length = 0;
    char *data;
    int ch;

    if (stream == NULL || buffer == NULL) {
        return -1;
    }

    data = malloc(capacity);
    if (data == NULL) {
        return -2;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
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

    if (ch == EOF && ferror(stream)) {
        free(data);
        return -3;
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
            fprintf(stderr, "Memory allocation failed\n");
        } else if (status == -3) {
            fprintf(stderr, "Input error\n");
        } else {
            fprintf(stderr, "Invalid input\n");
        }
        return EXIT_FAILURE;
    }

    cursor = input;

    if (parse_uintmax(&cursor, &a) != 0 ||
        parse_uintmax(&cursor, &b) != 0) {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' || a == 0 || b == 0) {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (lcm(a, b, &result) != 0) {
        free(input);
        fprintf(stderr, "LCM cannot be represented\n");
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        fprintf(stderr, "Output error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}