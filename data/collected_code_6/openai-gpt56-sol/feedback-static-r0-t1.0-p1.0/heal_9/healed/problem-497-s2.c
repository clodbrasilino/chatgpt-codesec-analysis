#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_surface_area(double radius, double height, double *area)
{
    const double pi = acos(-1.0);
    double slant_height;
    double sum;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    slant_height = hypot(radius, height);
    if (!isfinite(slant_height)) {
        return -1;
    }

    sum = radius + slant_height;
    if (!isfinite(sum)) {
        return -1;
    }

    if (radius != 0.0 && sum > DBL_MAX / pi / radius) {
        return -1;
    }

    *area = pi * radius * sum;
    return isfinite(*area) ? 0 : -1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char buffer[256];
    char *end;
    double parsed;
    size_t length;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return -1;
    }

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[--length] = '\0';
        if (length > 0 && buffer[length - 1] == '\r') {
            buffer[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed) ||
        parsed < 0.0) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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
    double radius;
    double height;
    double area;

    if (read_nonnegative_double("Enter the radius: ", &radius) != 0 ||
        read_nonnegative_double("Enter the height: ", &height) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cone_surface_area(radius, height, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}