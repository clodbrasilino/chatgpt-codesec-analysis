#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4095U
#define INPUT_BUFFER_SIZE (MAX_INPUT_LENGTH + 2U)

static int cube_surface_area(double side, double *area)
{
    if (area == NULL || !isfinite(side) || side < 0.0 ||
        side > sqrt(DBL_MAX / 6.0)) {
        return -1;
    }

    *area = 6.0 * side * side;
    return 0;
}

static int discard_line(FILE *stream)
{
    int ch;

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char *end;
    double side;
    double area;
    size_t length = 0U;

    if (fgets(input, (int)sizeof input, stdin) == NULL) {
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read the side length.\n", stderr);
                return EXIT_FAILURE;
            }
        } else if (ch != '\n') {
            if (discard_line(stdin) != 0) {
                fputs("Failed to read the side length.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid trailing input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_surface_area(side, &area) != 0) {
        fputs("Side length must be finite, nonnegative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}