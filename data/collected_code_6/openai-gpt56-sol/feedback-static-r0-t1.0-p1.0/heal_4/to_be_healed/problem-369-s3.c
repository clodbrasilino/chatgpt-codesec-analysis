#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int lateral_surface_area(double length, double width, double height,
                                double *area)
{
    double sum;

    if (area == NULL ||
        !isfinite(length) ||
        !isfinite(width) ||
        !isfinite(height) ||
        length < 0.0 ||
        width < 0.0 ||
        height < 0.0) {
        return 0;
    }

    if (length > DBL_MAX - width) {
        return 0;
    }

    sum = length + width;

    if (height > DBL_MAX / 2.0 ||
        (height != 0.0 && sum > DBL_MAX / (2.0 * height))) {
        return 0;
    }

    *area = 2.0 * height * sum;
    return isfinite(*area);
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

static int read_dimension(const char *name, double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    int ch;
    int result = 0;

    if (name == NULL || value == NULL) {
        return 0;
    }

    if (printf("Enter %s: ", name) < 0 || fflush(stdout) == EOF) {
        return 0;
    }

    capacity = 128;
    line = malloc(capacity);
    if (line == NULL) {
        discard_line();
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                discard_line();
                goto cleanup;
            }

            new_capacity = capacity * 2;
            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                discard_line();
                goto cleanup;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        goto cleanup;
    }

    line[length] = '\0';

    errno = 0;
    end = NULL;
    *value = strtod(line, &end);

    if (end == line ||
        errno == ERANGE ||
        !isfinite(*value) ||
        *value < 0.0) {
        goto cleanup;
    }

    while (*end == ' ' ||
           *end == '\t' ||
           *end == '\r' ||
           *end == '\v' ||
           *end == '\f') {
        ++end;
    }

    result = (*end == '\0');

cleanup:
    free(line);
    return result;
}

int main(void)
{
    double length;
    double width;
    double height;
    double area;

    if (!read_dimension("length", &length) ||
        !read_dimension("width", &width) ||
        !read_dimension("height", &height)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lateral_surface_area(length, width, height, &area)) {
        fputs("Unable to calculate the lateral surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}