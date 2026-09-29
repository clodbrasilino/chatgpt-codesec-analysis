#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_surface_area(double radius, double height, double *area)
{
    const double pi = acos(-1.0);
    double slant_height;
    double sum;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    slant_height = hypot(radius, height);
    if (!isfinite(slant_height)) {
        return -1;
    }

    sum = radius + slant_height;
    if (!isfinite(sum)) {
        return -1;
    }

    if (radius != 0.0 && sum > DBL_MAX / pi / radius) {
        return -1;
    }

    *area = pi * radius * sum;
    return isfinite(*area) ? 0 : -1;
}

static int discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return ferror(stream) ? -1 : 0;
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *buffer = NULL;
    char *end;
    double parsed;
    size_t capacity = 128;
    size_t length = 0;
    int ch;
    int result = -1;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                if (discard_line(stdin) != 0) {
                    goto cleanup;
                }
                goto cleanup;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                if (discard_line(stdin) != 0) {
                    goto cleanup;
                }
                goto cleanup;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        goto cleanup;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed) ||
        parsed < 0.0) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = parsed;
    result = 0;

cleanup:
    free(buffer);
    return result;
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