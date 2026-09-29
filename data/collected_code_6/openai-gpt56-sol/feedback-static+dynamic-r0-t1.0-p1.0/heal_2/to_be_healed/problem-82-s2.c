#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double sphere_volume(double radius)
{
    const double pi = 3.14159265358979323846;
    return (4.0 / 3.0) * pi * radius * radius * radius;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length + 1 >= capacity) {
        char *new_input = realloc(input, length + 1);

        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    char *end = NULL;
    double radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || radius < 0.0) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    double volume = sphere_volume(radius);

    if (!isfinite(volume)) {
        fputs("The calculated volume is out of range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}