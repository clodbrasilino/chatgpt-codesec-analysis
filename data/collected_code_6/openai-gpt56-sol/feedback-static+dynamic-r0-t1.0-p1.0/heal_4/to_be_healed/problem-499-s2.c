#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_diameter(double radius, double *diameter)
{
    if (diameter == NULL ||
        !isfinite(radius) ||
        radius < 0.0 ||
        radius > DBL_MAX / 2.0) {
        return -1;
    }

    *diameter = 2.0 * radius;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end = NULL;
    double radius;
    double diameter;
    int ch;
    int status = EXIT_FAILURE;

    fputs("Enter the radius: ", stdout);
    fflush(stdout);

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    fputs("Input is too long.\n", stderr);
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fputs("Unable to allocate memory.\n", stderr);
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read the radius.\n", stderr);
        goto cleanup;
    }

    if (length == 0 && ch == EOF) {
        fputs("Failed to read the radius.\n", stderr);
        goto cleanup;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            fputs("Unable to allocate memory.\n", stderr);
            goto cleanup;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = new_capacity;
    }

    input[length] = '\0';

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid radius.\n", stderr);
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || calculate_diameter(radius, &diameter) != 0) {
        fputs("Radius must be a finite, nonnegative number in range.\n", stderr);
        goto cleanup;
    }

    printf("Diameter: %.10g\n", diameter);
    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}