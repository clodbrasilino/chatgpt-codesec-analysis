#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 256

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

static int discard_remaining_input(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n' || !ferror(stdin);
}

static int read_positive_number(const char *prompt, double *value)
{
    char *buffer;
    char *end;
    double parsed;
    size_t capacity = INPUT_BUFFER_SIZE;
    size_t length = 0;
    int ch;

    if (prompt == NULL || value == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                if (!discard_remaining_input()) {
                    return 0;
                }
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                if (!discard_remaining_input()) {
                    return 0;
                }
                return 0;
            }

            buffer = resized;
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
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE ||
        !isfinite(parsed) || parsed < 0.0) {
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

    if (!read_positive_number("Triangle base: ", &base) ||
        !read_positive_number("Triangle height: ", &height) ||
        !read_positive_number("Prism length: ", &length)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!triangular_prism_volume(base, height, length, &volume)) {
        fputs("Unable to calculate a finite volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}