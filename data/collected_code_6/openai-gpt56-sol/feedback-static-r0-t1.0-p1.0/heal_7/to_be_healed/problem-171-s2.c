#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIDE_COUNT 5
#define INITIAL_CAPACITY 32
#define MAX_INPUT_LENGTH 4096

static int pentagon_perimeter(const double *sides, double *result)
{
    double perimeter = 0.0;

    if (sides == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
        if (!isfinite(sides[i]) || sides[i] <= 0.0) {
            return -1;
        }

        if (sides[i] > DBL_MAX - perimeter) {
            return -1;
        }

        perimeter += sides[i];
    }

    *result = perimeter;
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return (ch == EOF && ferror(stdin)) ? -1 : 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = INITIAL_CAPACITY;
    char *buffer;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    if (capacity > MAX_INPUT_LENGTH + 1U) {
        capacity = MAX_INPUT_LENGTH + 1U;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == MAX_INPUT_LENGTH) {
            if (discard_line() != 0) {
                free(buffer);
                return -1;
            }

            free(buffer);
            return -1;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity >= MAX_INPUT_LENGTH + 1U) {
                free(buffer);
                return -1;
            }

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        free(buffer);
        return -1;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_side(double *side)
{
    char *input;
    char *end;
    double value;

    if (side == NULL || read_line(&input) != 0) {
        return -1;
    }

    errno = 0;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(value) || value <= 0.0) {
        free(input);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return -1;
    }

    *side = value;
    free(input);
    return 0;
}

int main(void)
{
    double sides[SIDE_COUNT];
    double perimeter;

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
        if (read_side(&sides[i]) != 0) {
            fputs("Each side must be a positive finite number.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (pentagon_perimeter(sides, &perimeter) != 0) {
        fputs("Unable to calculate the perimeter.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}