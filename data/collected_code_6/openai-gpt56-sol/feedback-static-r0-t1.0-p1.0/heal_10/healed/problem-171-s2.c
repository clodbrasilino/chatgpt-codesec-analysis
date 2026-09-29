#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define SIDE_COUNT 5U
#define MAX_INPUT_LENGTH 4096U

static int pentagon_perimeter(const double sides[SIDE_COUNT], double *result)
{
    double perimeter = 0.0;

    if (sides == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
        if (!isfinite(sides[i]) || sides[i] <= 0.0 ||
            perimeter > DBL_MAX - sides[i]) {
            return -1;
        }

        perimeter += sides[i];
    }

    *result = perimeter;
    return 0;
}

static int discard_remainder(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return -1;
    }

    do {
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return ferror(stream) ? -1 : 0;
}

static int read_line(FILE *stream, char *buffer, size_t capacity)
{
    size_t length;

    if (stream == NULL || buffer == NULL ||
        capacity < 2U || capacity > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stream) == NULL) {
        return -1;
    }

    length = 0U;
    while (length < capacity && buffer[length] != '\0') {
        ++length;
    }

    if (length == capacity) {
        buffer[capacity - 1U] = '\0';
        return -1;
    }

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[--length] = '\0';

        if (length > 0U && buffer[length - 1U] == '\r') {
            buffer[length - 1U] = '\0';
        }

        return 0;
    }

    if (feof(stream)) {
        if (length == 0U) {
            return -1;
        }

        if (buffer[length - 1U] == '\r') {
            buffer[length - 1U] = '\0';
        }

        return 0;
    }

    return discard_remainder(stream) == 0 ? -1 : -1;
}

static int read_side(FILE *stream, double *side)
{
    char *input;
    char *end;
    double value;
    int status = -1;

    if (stream == NULL || side == NULL) {
        return -1;
    }

    input = malloc(MAX_INPUT_LENGTH + 2U);
    if (input == NULL) {
        return -1;
    }

    if (read_line(stream, input, MAX_INPUT_LENGTH + 2U) != 0) {
        goto cleanup;
    }

    errno = 0;
    end = NULL;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(value) || value <= 0.0) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *side = value;
    status = 0;

cleanup:
    free(input);
    return status;
}

int main(void)
{
    double sides[SIDE_COUNT];
    double perimeter;

    for (size_t i = 0U; i < SIDE_COUNT; ++i) {
        if (read_side(stdin, &sides[i]) != 0) {
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