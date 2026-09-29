#include <ctype.h>
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

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0U;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length >= MAX_INPUT_LENGTH) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            free(buffer);

            if (ch == EOF && ferror(stdin)) {
                return -1;
            }

            return -2;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
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

    while (*end != '\0' && isspace((unsigned char)*end)) {
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