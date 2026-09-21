#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    READ_ERROR = -1,
    READ_TOO_LARGE = -2,
    READ_SUCCESS = 0,
    MAX_INPUT_LENGTH = 4096
};

static int calculate_diameter(double radius, double *diameter)
{
    if (diameter == NULL || !isfinite(radius) ||
        radius < 0.0 || radius > DBL_MAX / 2.0) {
        return -1;
    }

    *diameter = radius * 2.0;
    return 0;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? READ_ERROR : READ_SUCCESS;
}

static int read_radius(double *radius)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH + 1];
    char *end;
    size_t length = 0;
    int ch;
    double value;

    if (radius == NULL) {
        return READ_ERROR;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == MAX_INPUT_LENGTH) {
            if (discard_line() != READ_SUCCESS) {
                return READ_ERROR;
            }

            return READ_TOO_LARGE;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin) || length == 0) {
            return READ_ERROR;
        }
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        return READ_ERROR;
    }

    while (*end == ' ' || *end == '\t' || *end == '\v' ||
           *end == '\f' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0' || !isfinite(value)) {
        return READ_ERROR;
    }

    *radius = value;
    return READ_SUCCESS;
}

int main(void)
{
    double radius;
    double diameter;
    int status = read_radius(&radius);

    if (status == READ_TOO_LARGE) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != READ_SUCCESS ||
        calculate_diameter(radius, &diameter) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", diameter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}