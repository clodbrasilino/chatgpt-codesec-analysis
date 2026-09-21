#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIDE_COUNT 5
#define INPUT_SIZE 128

static int pentagon_perimeter(const double *sides, size_t count,
                              double *result)
{
    if (sides == NULL || result == NULL || count != SIDE_COUNT) {
        return -1;
    }

    double perimeter = 0.0;

    for (size_t i = 0; i < count; ++i) {
        if (!isfinite(sides[i]) || sides[i] <= 0.0 ||
            sides[i] > DBL_MAX - perimeter) {
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

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    }

    return 0;
}

static int read_line(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2 || capacity > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    size_t length = strnlen(buffer, capacity);

    if (length == capacity) {
        buffer[capacity - 1] = '\0';
        if (discard_line() != 0) {
            return -1;
        }
        return -1;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';

        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[length - 1] = '\0';
        }

        return 0;
    }

    if (feof(stdin)) {
        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[length - 1] = '\0';
        }

        return 0;
    }

    if (discard_line() != 0) {
        return -1;
    }

    return -1;
}

static int read_side(double *side)
{
    if (side == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];

    if (read_line(input, sizeof input) != 0) {
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

    if (pentagon_perimeter(sides, SIDE_COUNT, &perimeter) != 0) {
        fputs("Unable to calculate the perimeter.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}