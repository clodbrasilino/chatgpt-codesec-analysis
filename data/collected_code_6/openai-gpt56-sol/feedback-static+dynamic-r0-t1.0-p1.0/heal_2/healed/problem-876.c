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
    uintmax_t quotient;

    if (a == 0 || b == 0 || result == NULL) {
        return -1;
    }

    divisor = gcd(a, b);
    quotient = a / divisor;

    if (quotient > UINTMAX_MAX / b) {
        return -1;
    }

    *result = quotient * b;
    return 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            capacity *= 2;
            resized = realloc(buffer, capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_values(uintmax_t *a, uintmax_t *b)
{
    char *buffer;
    char *cursor;
    char *end;
    int status = -1;

    if (a == NULL || b == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    cursor = buffer;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        goto cleanup;
    }

    errno = 0;
    *a = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || *a == 0) {
        goto cleanup;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        goto cleanup;
    }

    errno = 0;
    *b = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || *b == 0) {
        goto cleanup;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        goto cleanup;
    }

    status = 0;

cleanup:
    free(buffer);
    return status;
}

int main(void)
{
    uintmax_t a;
    uintmax_t b;
    uintmax_t result;

    if (read_values(&a, &b) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (lcm(a, b, &result) != 0) {
        fputs("LCM cannot be represented\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", result);
    return EXIT_SUCCESS;
}