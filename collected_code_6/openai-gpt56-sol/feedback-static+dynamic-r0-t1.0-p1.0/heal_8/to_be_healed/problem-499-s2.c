#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
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

    *diameter = radius * 2.0;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    size_t capacity = 0;
    size_t length = 0;
    double radius;
    double diameter;
    int ch;
    int status = EXIT_FAILURE;

    fputs("Enter the radius: ", stdout);
    if (fflush(stdout) == EOF) {
        fputs("Failed to write the prompt.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        char *resized;
        size_t new_capacity;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            fputs("Input is too long.\n", stderr);
            goto cleanup;
        }

        if (capacity <= length + 1) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    fputs("Input is too long.\n", stderr);
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                fputs("Failed to allocate input buffer.\n", stderr);
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fputs("Failed to read the radius.\n", stderr);
        goto cleanup;
    }

    if (ch == EOF && length == 0) {
        fputs("Failed to read the radius.\n", stderr);
        goto cleanup;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Failed to allocate input buffer.\n", stderr);
            goto cleanup;
        }
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

    if (printf("Diameter: %.10g\n", diameter) < 0) {
        fputs("Failed to write the result.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}