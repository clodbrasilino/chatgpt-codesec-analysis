#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum { SIDE_COUNT = 5, INPUT_SIZE = 128 };

static int pentagon_perimeter(const double sides[static SIDE_COUNT],
                              double *result)
{
    double perimeter = 0.0;

    if (sides == NULL || result == NULL) {
        return -1;
    }

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

static int discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_SIZE];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i = 0;

        while (buffer[i] != '\0' && buffer[i] != '\n') {
            ++i;
        }

        if (buffer[i] == '\n') {
            return 0;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_side(double *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    char *start;
    char *end;

    if (value == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] != '\n' && !feof(stdin)) {
        if (discard_line() != 0) {
            return -1;
        }
        return -1;
    }

    start = input;

    while (*start == ' ' || *start == '\t' || *start == '\n' ||
           *start == '\r' || *start == '\f' || *start == '\v') {
        ++start;
    }

    errno = 0;
    double parsed = strtod(start, &end);

    if (end == start || errno == ERANGE ||
        !isfinite(parsed) || parsed <= 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(void)
{
    double sides[SIDE_COUNT];
    double perimeter;

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
        if (read_side(&sides[i]) != 0) {
            fputs("Invalid side length\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (pentagon_perimeter(sides, &perimeter) != 0) {
        fputs("Unable to calculate perimeter\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}