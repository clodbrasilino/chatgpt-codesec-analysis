#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_surface_area(double radius, double height, double *area)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    result = 2.0 * pi * radius * (radius + height);

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end;
    double parsed_value;
    int ch;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    end = buffer;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end != '\n') {
        if (!feof(stdin)) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin)) {
                return -1;
            }
        }

        return -1;
    }

    *end = '\0';

    errno = 0;
    end = NULL;
    parsed_value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed_value) ||
        parsed_value < 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed_value;
    return 0;
}

int main(void)
{
    double radius;
    double height;
    double area;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the height: ", &height) != 0) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cylinder_surface_area(radius, height, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}