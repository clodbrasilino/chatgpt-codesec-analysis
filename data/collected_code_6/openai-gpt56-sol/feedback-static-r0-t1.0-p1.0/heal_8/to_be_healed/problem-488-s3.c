#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4095U

static int pentagon_area(double side, double *area)
{
    const double factor =
        0.25 * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0)));
    const double limit = sqrt(DBL_MAX / factor);

    if (area == NULL || !isfinite(side) || side <= 0.0 || side > limit) {
        return -1;
    }

    *area = factor * side * side;

    return isfinite(*area) ? 0 : -1;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_line(char **line)
{
    char *buffer;
    size_t length;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc((size_t)MAX_INPUT_LENGTH + 2U);

    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        free(buffer);
        return -1;
    }

    length = 0U;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        if (discard_line() != 0) {
            free(buffer);
            return -1;
        }

        free(buffer);
        return -2;
    } else if (!feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            if (discard_line() != 0) {
                free(buffer);
                return -1;
            }

            free(buffer);
            return -2;
        }

        if (ferror(stdin)) {
            free(buffer);
            return -1;
        }
    }

    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    double side;
    double area;
    int result;

    if (fputs("Enter the side length of a regular pentagon: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Failed to write prompt.\n", stderr);
        return EXIT_FAILURE;
    }

    result = read_line(&input);

    if (result == -2) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (result != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (pentagon_area(side, &area) != 0) {
        fputs(
            "The side length must be a finite positive number with a representable area.\n",
            stderr
        );
        return EXIT_FAILURE;
    }

    if (printf("Area: %.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}