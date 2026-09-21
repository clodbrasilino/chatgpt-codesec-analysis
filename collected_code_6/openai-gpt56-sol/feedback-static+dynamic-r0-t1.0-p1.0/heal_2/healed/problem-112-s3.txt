#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 256

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
    char input[INPUT_BUFFER_SIZE];
    char *end;
    double parsed;
    int ch;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    for (size_t i = 0; input[i] != '\0'; ++i) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }

        if (i == sizeof input - 2) {
            ch = fgetc(stdin);
            if (ch != '\n' && ch != EOF) {
                do {
                    ch = fgetc(stdin);
                } while (ch != '\n' && ch != EOF);
                return -1;
            }

            if (ch == EOF && ferror(stdin)) {
                return -1;
            }
        }
    }

    errno = 0;
    end = NULL;
    parsed = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
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