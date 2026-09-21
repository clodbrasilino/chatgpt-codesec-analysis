#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

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

static char *read_line(FILE *stream, size_t *out_length)
{
    size_t capacity = 128u;
    size_t length = 0u;
    char *buffer;
    int ch;

    if (stream == NULL || out_length == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        if (length + 1u >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2u) {
                free(buffer);
                return NULL;
            }
            new_capacity = capacity * 2u;

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stream) != 0 || (length == 0u && ch == EOF)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    *out_length = length;
    return buffer;
}

int main(void)
{
    char *buffer = NULL;
    size_t length = 0u;
    char *cursor = NULL;
    int a = 0;
    int b = 0;
    int product = 0;

    if (printf("Enter two integers separated by a space: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    buffer = read_line(stdin, &length);
    if (buffer == NULL) {
        (void)fprintf(stderr, "Error: could not read input.\n");
        return EXIT_FAILURE;
    }

    if (memchr(buffer, '\0', length) != NULL) {
        (void)fprintf(stderr, "Error: input contains invalid NUL bytes.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (!parse_int(buffer, &cursor, &a) || !parse_int(cursor, &cursor, &b)) {
        (void)fprintf(stderr, "Error: input must contain two valid integers.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        cursor++;
    }

    if (*cursor != '\0') {
        (void)fprintf(stderr, "Error: unexpected trailing characters in input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    buffer = NULL;

    if (!multiply_integers(a, b, &product)) {
        (void)fprintf(stderr, "Error: %d * %d is outside the range of int.\n", a, b);
        return EXIT_FAILURE;
    }

    if (printf("%d * %d = %d\n", a, b, product) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}