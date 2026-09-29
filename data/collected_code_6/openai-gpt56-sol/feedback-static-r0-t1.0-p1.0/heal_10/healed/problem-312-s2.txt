#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 256

static int cone_volume(double radius, double height, double *volume)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (volume == NULL ||
        !isfinite(radius) ||
        !isfinite(height) ||
        radius < 0.0 ||
        height < 0.0) {
        return -1;
    }

    result = (pi * radius * radius * height) / 3.0;

    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

static int read_line(char **buffer)
{
    size_t capacity = INPUT_SIZE;
    size_t length = 0;
    char *line;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    line = malloc(capacity);

    if (line == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                free(line);
                return -1;
            }

            if (ch == EOF && length == 0) {
                free(line);
                return -1;
            }

            break;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(line, new_capacity);

            if (resized == NULL) {
                free(line);
                return -1;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    line[length] = '\0';
    *buffer = line;
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *buffer;
    char *end;
    double parsed_value;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (read_line(&buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed_value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed_value) ||
        parsed_value < 0.0) {
        free(buffer);
        return -1;
    }

    while (*end != '\0') {
        if (!isspace((unsigned char)*end)) {
            free(buffer);
            return -1;
        }
        ++end;
    }

    free(buffer);
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