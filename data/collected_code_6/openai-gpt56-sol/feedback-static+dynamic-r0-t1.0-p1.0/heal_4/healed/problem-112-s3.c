#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    const double pi = acos(-1.0);
    double perimeter;

    if (result == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    perimeter = 2.0 * (2.0 * pi * radius + height);

    if (!isfinite(perimeter)) {
        return -1;
    }

    *result = perimeter;
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *line = NULL;
    char *end;
    double parsed;
    size_t capacity = 0;
    ssize_t length;
    int status = -1;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return -1;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }

    errno = 0;
    end = NULL;
    parsed = strtod(line, &end);

    if (end != line && errno != ERANGE && isfinite(parsed) && parsed >= 0.0) {
        while (*end != '\0' && isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end == '\0') {
            *value = parsed;
            status = 0;
        }
    }

    free(line);
    return status;
}

int main(void)
{
    double radius;
    double height;
    double perimeter;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the height: ", &height) != 0) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cylinder_perimeter(radius, height, &perimeter) != 0) {
        fputs("Unable to calculate the perimeter.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Cylinder perimeter: %.6f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}