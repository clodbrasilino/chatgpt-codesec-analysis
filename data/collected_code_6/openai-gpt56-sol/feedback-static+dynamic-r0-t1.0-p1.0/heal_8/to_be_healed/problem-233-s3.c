#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double radius, double height, double *area)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (area == NULL ||
        !isfinite(radius) ||
        !isfinite(height) ||
        radius < 0.0 ||
        height < 0.0) {
        return 0;
    }

    if (radius != 0.0 && height > (DBL_MAX / (2.0 * pi)) / radius) {
        return 0;
    }

    result = 2.0 * pi * radius * height;

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    *line = NULL;
    *capacity = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length + 1 >= *capacity) {
            if (*capacity == 0) {
                new_capacity = 128;
            } else {
                if (*capacity > (SIZE_MAX / 2)) {
                    free(*line);
                    *line = NULL;
                    *capacity = 0;
                    return 0;
                }
                new_capacity = *capacity * 2;
            }

            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return 0;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(*line);
        *line = NULL;
        *capacity = 0;
        return 0;
    }

    if (length + 1 >= *capacity) {
        char *resized;

        if (length == SIZE_MAX) {
            free(*line);
            *line = NULL;
            *capacity = 0;
            return 0;
        }

        resized = realloc(*line, length + 1);
        if (resized == NULL) {
            free(*line);
            *line = NULL;
            *capacity = 0;
            return 0;
        }

        *line = resized;
        *capacity = length + 1;
    }

    (*line)[length] = '\0';
    return 1;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *line;
    char *end;
    size_t capacity;
    double parsed;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (!read_line(&line, &capacity)) {
        return 0;
    }

    errno = 0;
    parsed = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(parsed) ||
        parsed < 0.0) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    free(line);
    *value = parsed;
    return 1;
}

int main(void)
{
    double radius;
    double height;
    double area;

    if (!read_nonnegative_double("Enter the radius: ", &radius) ||
        !read_nonnegative_double("Enter the height: ", &height)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lateral_surface_area(radius, height, &area)) {
        fputs("Unable to calculate the lateral surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}