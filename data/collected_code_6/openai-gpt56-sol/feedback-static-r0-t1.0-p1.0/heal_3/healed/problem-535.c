#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_surface_area(double radius, double *area)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (area == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = pi * radius * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    char *buffer;
    int ch;

    if (line == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;

        if (length == capacity - 1) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end;
    double radius;
    double area;
    int read_status;

    fputs("Enter the cylinder radius: ", stdout);
    fflush(stdout);

    read_status = read_line(&input);
    if (read_status <= 0) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (radius < 0.0) {
        fputs("Radius must be a non-negative number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_surface_area(radius, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Top or bottom surface area: %.10g\n", area);
    return EXIT_SUCCESS;
}