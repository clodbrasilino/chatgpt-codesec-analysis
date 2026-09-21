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

static int read_line(FILE *stream, char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;
    int ch;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (length >= capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream) || (ch == EOF && length == 0)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_values(uintmax_t *a, uintmax_t *b)
{
    char *buffer = NULL;
    char *cursor;
    char *end;
    uintmax_t first;
    uintmax_t second;
    int status = -1;

    if (a == NULL || b == NULL || read_line(stdin, &buffer) != 0) {
        return -1;
    }

    cursor = buffer;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-' || *cursor == '+') {
        goto cleanup;
    }

    errno = 0;
    first = strtoumax(cursor, &end, 10);
    if (end == cursor || errno == ERANGE || first == 0) {
        goto cleanup;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-' || *cursor == '+') {
        goto cleanup;
    }

    errno = 0;
    second = strtoumax(cursor, &end, 10);
    if (end == cursor || errno == ERANGE || second == 0) {
        goto cleanup;
    }

    cursor = end;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        goto cleanup;
    }

    *a = first;
    *b = second;
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

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}