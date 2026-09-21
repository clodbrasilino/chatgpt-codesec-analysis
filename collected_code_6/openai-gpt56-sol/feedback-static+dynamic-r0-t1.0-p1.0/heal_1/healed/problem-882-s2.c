#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_perimeter(double side_a, double side_b, double *perimeter)
{
    double sum;

    if (perimeter == NULL ||
        !isfinite(side_a) ||
        !isfinite(side_b) ||
        side_a <= 0.0 ||
        side_b <= 0.0 ||
        side_a > DBL_MAX - side_b) {
        return 0;
    }

    sum = side_a + side_b;

    if (sum > DBL_MAX / 2.0) {
        return 0;
    }

    *perimeter = 2.0 * sum;
    return isfinite(*perimeter);
}

static int read_positive_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (buffer[0] == '\0') {
        return 0;
    }

    end = buffer;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end != '\n' && !feof(stdin)) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return 0;
    }

    errno = 0;
    *value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(*value) ||
        *value <= 0.0) {
        return 0;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\n' ||
           *end == '\r' ||
           *end == '\f' ||
           *end == '\v') {
        ++end;
    }

    return *end == '\0';
}

int main(void)
{
    double side_a;
    double side_b;
    double perimeter;

    if (!read_positive_double("Enter the first side length: ", &side_a) ||
        !read_positive_double("Enter the second side length: ", &side_b)) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!calculate_perimeter(side_a, side_b, &perimeter)) {
        if (fputs("Unable to calculate the perimeter.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}