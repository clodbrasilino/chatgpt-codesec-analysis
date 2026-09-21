#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 256

static int triangular_prism_volume(double base, double height, double length,
                                   double *volume)
{
    double result;

    if (volume == NULL ||
        !isfinite(base) || !isfinite(height) || !isfinite(length) ||
        base < 0.0 || height < 0.0 || length < 0.0) {
        return 0;
    }

    result = 0.5 * base * height * length;

    if (!isfinite(result)) {
        return 0;
    }

    *volume = result;
    return 1;
}

static int read_positive_number(const char *prompt, double *value)
{
    char buffer[INPUT_BUFFER_SIZE];
    char *end;
    double parsed;
    size_t length;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == sizeof buffer || buffer[length] == '\0') {
        int ch;

        if (length == 0 || buffer[length - 1] != '\n') {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ch == EOF && ferror(stdin)) {
                return 0;
            }

            return 0;
        }
    } else {
        buffer[length] = '\0';
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE ||
        !isfinite(parsed) || parsed < 0.0) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    double base;
    double height;
    double length;
    double volume;

    if (!read_positive_number("Triangle base: ", &base) ||
        !read_positive_number("Triangle height: ", &height) ||
        !read_positive_number("Prism length: ", &length)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!triangular_prism_volume(base, height, length, &volume)) {
        fputs("Unable to calculate a finite volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}