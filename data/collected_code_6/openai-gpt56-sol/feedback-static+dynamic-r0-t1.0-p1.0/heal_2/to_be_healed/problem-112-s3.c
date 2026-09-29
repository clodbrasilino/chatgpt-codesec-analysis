#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    double pi;
    double perimeter;

    if (result == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    pi = acos(-1.0);
    perimeter = 2.0 * (2.0 * pi * radius + height);

    if (!isfinite(perimeter)) {
        return -1;
    }

    *result = perimeter;
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *input = NULL;
    char *end;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return -1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return -1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(input);
        return -1;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return -1;
        }
    }

    input[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        free(input);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return -1;
    }

    *value = parsed;
    free(input);
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