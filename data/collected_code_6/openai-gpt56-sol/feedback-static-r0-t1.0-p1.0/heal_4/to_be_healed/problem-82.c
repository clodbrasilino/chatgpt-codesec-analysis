#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_volume(double radius, double *volume)
{
    static const double pi = 3.14159265358979323846;
    double result;

    if (volume == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = (4.0 / 3.0) * pi * radius * radius * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end;
    double radius;
    double volume;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *new_input;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    free(input);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate input buffer.\n", stderr);
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
        char *new_input;
        size_t new_capacity = length + 1;

        new_input = realloc(input, new_capacity);
        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate input buffer.\n", stderr);
            return EXIT_FAILURE;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || sphere_volume(radius, &volume) != 0) {
        free(input);
        fputs("Invalid radius or volume out of range.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}