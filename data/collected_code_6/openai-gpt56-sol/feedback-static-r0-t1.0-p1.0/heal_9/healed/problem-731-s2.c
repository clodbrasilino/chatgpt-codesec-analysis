#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_lateral_surface_area(double radius, double slant_height,
                                     double *area)
{
    const double pi = 3.14159265358979323846;

    if (area == NULL ||
        !isfinite(radius) ||
        !isfinite(slant_height) ||
        radius < 0.0 ||
        slant_height < 0.0) {
        return 0;
    }

    if (radius != 0.0 && slant_height > (DBL_MAX / pi) / radius) {
        return 0;
    }

    *area = pi * radius * slant_height;
    return isfinite(*area);
}

static int discard_remaining_input(void)
{
    char buffer[4096];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i;

        for (i = 0; buffer[i] != '\0'; ++i) {
            if (buffer[i] == '\n') {
                return 1;
            }
        }
    }

    return !ferror(stdin);
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        size_t available = capacity - length;

        if (available < 2) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                discard_remaining_input();
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                discard_remaining_input();
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
            available = capacity - length;
        }

        if (fgets(buffer + length, (int)(available > INT_MAX
                                            ? INT_MAX
                                            : available),
                  stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            *line = buffer;
            return 1;
        }

        if (feof(stdin)) {
            break;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *buffer = NULL;
    char *end;
    double parsed_value;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed_value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(parsed_value) ||
        parsed_value < 0.0) {
        free(buffer);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    free(buffer);
    *value = parsed_value;
    return 1;
}

int main(void)
{
    double radius;
    double slant_height;
    double area;

    if (!read_nonnegative_double("Enter the radius: ", &radius) ||
        !read_nonnegative_double("Enter the slant height: ", &slant_height)) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!cone_lateral_surface_area(radius, slant_height, &area)) {
        if (fputs("Unable to calculate the area.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}