#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_volume(double radius, double height, double *volume)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (volume == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    result = pi * radius * radius * height;

    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    double result;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(input);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    free(input);
                    return -1;
                }
                new_capacity = capacity * 2;
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

    if (length == (size_t)-1) {
        free(input);
        return -1;
    }

    if (length + 1 > capacity) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            return -1;
        }

        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    result = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(result) || result < 0.0) {
        free(input);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return -1;
    }

    *value = result;
    free(input);
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

    if (cylinder_volume(radius, height, &volume) != 0) {
        fputs("Unable to calculate the volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}