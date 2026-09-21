#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIDE_COUNT 5
#define INPUT_SIZE 128

static int pentagon_perimeter(const double sides[static SIDE_COUNT],
                              double *result)
{
    if (sides == NULL || result == NULL) {
        return -1;
    }

    double perimeter = 0.0;

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
        if (!isfinite(sides[i]) || sides[i] <= 0.0 ||
            sides[i] > DBL_MAX - perimeter) {
            return -1;
        }

        perimeter += sides[i];
    }

    *result = perimeter;
    return 0;
}

static int read_line(char buffer[static INPUT_SIZE])
{
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, INPUT_SIZE, stdin) == NULL) {
        return -1;
    }

    size_t length = 0;

    while (length < INPUT_SIZE && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        if (buffer[length] == '\r') {
            break;
        }
        ++length;
    }

    if (length < INPUT_SIZE && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    if (length < INPUT_SIZE && buffer[length] == '\r') {
        buffer[length] = '\0';

        int ch = fgetc(stdin);
        if (ch == '\n' || ch == EOF) {
            return (ch == EOF && ferror(stdin)) ? -1 : 0;
        }

        while (ch != '\n' && ch != EOF) {
            ch = fgetc(stdin);
        }

        return -1;
    }

    if (feof(stdin)) {
        return 0;
    }

    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return -1;
}

static int read_side(double *side)
{
    if (side == NULL) {
        return -1;
    }

    char input[INPUT_SIZE];

    if (read_line(input) != 0) {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    double value = strtod(input, &end);

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
        if (read_side(&sides[i]) != 0) {
            fputs("Each side must be a positive finite number on a complete line.\n",
                  stderr);
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