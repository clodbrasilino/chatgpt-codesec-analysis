#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cone_surface_area(double radius, double height, double *area)
{
    double slant_height;
    double sum;
    double result;
    const double pi = acos(-1.0);

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0 || !isfinite(pi)) {
        return -1;
    }

    if (radius == 0.0) {
        *area = 0.0;
        return 0;
    }

    slant_height = hypot(radius, height);
    if (!isfinite(slant_height) || slant_height > DBL_MAX - radius) {
        return -1;
    }

    sum = radius + slant_height;
    if (radius > DBL_MAX / sum) {
        return -1;
    }

    result = radius * sum;
    if (result > DBL_MAX / pi) {
        return -1;
    }

    result *= pi;
    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int read_line(char **line)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    buffer[0] = '\0';

    for (;;) {
        size_t available;
        char *result;
        char *newline;

        available = capacity - length;
        if (available < 2 || available > (size_t)INT_MAX) {
            free(buffer);
            return -1;
        }

        result = fgets(buffer + length, (int)available, stdin);
        if (result == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        newline = strchr(buffer + length, '\n');
        if (newline != NULL) {
            *newline = '\0';
            length = (size_t)(newline - buffer);
            break;
        }

        length += strlen(buffer + length);

        if (feof(stdin)) {
            break;
        }

        if (length + 1 < capacity) {
            continue;
        }

        if (capacity > SIZE_MAX / 2) {
            free(buffer);
            return -1;
        }

        {
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }
    }

    *line = buffer;
    return 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *line = NULL;
    char *start;
    char *end;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (read_line(&line) != 0) {
        return -1;
    }

    start = line;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtod(start, &end);

    if (end == start || errno == ERANGE || !isfinite(parsed) || parsed < 0.0) {
        free(line);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = parsed;
    free(line);
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