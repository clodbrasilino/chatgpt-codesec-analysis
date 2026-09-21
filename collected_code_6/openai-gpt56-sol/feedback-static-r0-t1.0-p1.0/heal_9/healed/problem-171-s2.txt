#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define SIDE_COUNT 5
#define MAX_INPUT_LENGTH 4096

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

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    if (ch == EOF && ferror(stream)) {
        return -1;
    }

    return 0;
}

static int read_line(FILE *stream, char *buffer, size_t capacity)
{
    size_t length;

    if (stream == NULL || buffer == NULL || capacity < 2 ||
        capacity > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stream) == NULL) {
        return -1;
    }

    length = 0;
    while (length < capacity && buffer[length] != '\0') {
        ++length;
    }

    if (length == capacity) {
        buffer[capacity - 1] = '\0';
        return -1;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';

        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[length - 1] = '\0';
        }

        return 0;
    }

    if (feof(stream)) {
        if (length == 0) {
            return -1;
        }

        if (buffer[length - 1] == '\r') {
            buffer[length - 1] = '\0';
        }

        return 0;
    }

    if (discard_remainder(stream) != 0) {
        return -1;
    }

    return -1;
}

static int read_side(FILE *stream, double *side)
{
    char input[MAX_INPUT_LENGTH + 2U];
    char *end;
    double value;

    if (stream == NULL || side == NULL) {
        return -1;
    }

    if (read_line(stream, input, sizeof(input)) != 0) {
        return -1;
    }

    errno = 0;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(value) || value <= 0.0) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *side = value;
    return 0;
}

int main(void)
{
    double sides[SIDE_COUNT];
    double perimeter;

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
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