#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_volume(double radius, double height, double *volume)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (volume == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    result = (pi * radius * radius * height) / 3.0;

    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
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

    if (buffer[0] == '\0') {
        return -1;
    }

    end = buffer;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (*end == '\0') {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return -1;
        }
    }

    errno = 0;
    parsed_value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed_value) ||
        parsed_value < 0.0) {
        return -1;
    }

    while (*end != '\0') {
        if (*end != ' ' && *end != '\t' && *end != '\r' &&
            *end != '\v' && *end != '\f') {
            return -1;
        }
        ++end;
    }

    *value = parsed_value;
    return 0;
}

int main(void)
{
    double radius;
    double height;
    double volume;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_nonnegative_double("Enter the height: ", &height) != 0) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cone_volume(radius, height, &volume) != 0) {
        fputs("Unable to calculate the cone volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume of the cone: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}