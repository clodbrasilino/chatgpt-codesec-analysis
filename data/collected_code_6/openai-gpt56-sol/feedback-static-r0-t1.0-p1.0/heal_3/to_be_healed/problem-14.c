#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int triangular_prism_volume(double base, double height, double length,
                                   double *volume)
{
    double result;

    if (volume == NULL ||
        !isfinite(base) || !isfinite(height) || !isfinite(length) ||
        base < 0.0 || height < 0.0 || length < 0.0) {
        return 0;
    }

    result = 0.5 * base * height * length;
    if (!isfinite(result)) {
        return 0;
    }

    *volume = result;
    return 1;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n';
}

static int read_nonnegative_double(const char *prompt, double *value)
{
    char *buffer;
    char *end;
    double parsed;
    size_t capacity;
    size_t length;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    capacity = 128;
    length = 0;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            char *new_buffer;
            size_t new_capacity;

            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                discard_line();
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                discard_line();
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE ||
        !isfinite(parsed) || parsed < 0.0) {
        free(buffer);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = parsed;
    free(buffer);
    return 1;
}

int main(void)
{
    double base;
    double height;
    double length;
    double volume;

    if (!read_nonnegative_double("Enter triangle base: ", &base) ||
        !read_nonnegative_double("Enter triangle height: ", &height) ||
        !read_nonnegative_double("Enter prism length: ", &length)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!triangular_prism_volume(base, height, length, &volume)) {
        fputs("Unable to calculate volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}