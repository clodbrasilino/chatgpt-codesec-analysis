#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>
#include <stdint.h>

static bool multiply_integers(int a, int b, int *result)
{
    bool negative;
    unsigned int multiplicand;
    unsigned int multiplier;
    unsigned int product = 0u;

    if (result == NULL) {
        return false;
    }

    if (a == 0 || b == 0) {
        *result = 0;
        return true;
    }

    if ((a > 0 && b > 0 && a > INT_MAX / b) ||
        (a > 0 && b < 0 && b < INT_MIN / a) ||
        (a < 0 && b > 0 && a < INT_MIN / b) ||
        (a < 0 && b < 0 && a < INT_MAX / b)) {
        return false;
    }

    negative = ((a < 0) != (b < 0));
    multiplicand = (a < 0) ? (0u - (unsigned int)a) : (unsigned int)a;
    multiplier = (b < 0) ? (0u - (unsigned int)b) : (unsigned int)b;

    while (multiplier != 0u) {
        if ((multiplier & 1u) != 0u) {
            product += multiplicand;
        }
        multiplicand <<= 1;
        multiplier >>= 1;
    }

    if (negative) {
        if (product == (unsigned int)INT_MAX + 1u) {
            *result = INT_MIN;
        } else {
            *result = -(int)product;
        }
    } else {
        *result = (int)product;
    }

    return true;
}

static bool parse_int(const char *start, char **end, int *out)
{
    long value;

    if (start == NULL || end == NULL || out == NULL) {
        return false;
    }

    errno = 0;
    value = strtol(start, end, 10);

    if (*end == start || errno == ERANGE ||
        value > (long)INT_MAX || value < (long)INT_MIN) {
        return false;
    }

    *out = (int)value;
    return true;
}

static bool read_line(FILE *stream, char **out)
{
    size_t capacity = 64u;
    size_t length = 0u;
    char *buffer;
    int ch;

    if (stream == NULL || out == NULL) {
        return false;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1u >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2u) {
                free(buffer);
                return false;
            }

            new_capacity = capacity * 2u;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream) != 0 || (ch == EOF && length == 0u)) {
        free(buffer);
        return false;
    }

    buffer[length] = '\0';
    *out = buffer;
    return true;
}

int main(void)
{
    char *buffer = NULL;
    char *cursor = NULL;
    int a = 0;
    int b = 0;
    int product = 0;
    int status = EXIT_FAILURE;

    if (printf("Enter two integers separated by a space: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (!read_line(stdin, &buffer)) {
        (void)fprintf(stderr, "Error: could not read input.\n");
        return EXIT_FAILURE;
    }

    if (!parse_int(buffer, &cursor, &a) || !parse_int(cursor, &cursor, &b)) {
        (void)fprintf(stderr, "Error: input must contain two valid integers.\n");
        goto cleanup;
    }

    if (!multiply_integers(a, b, &product)) {
        (void)fprintf(stderr, "Error: %d * %d is outside the range of int.\n", a, b);
        goto cleanup;
    }

    if (printf("%d * %d = %d\n", a, b, product) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(buffer);
    return status;
}