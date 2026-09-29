#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_diameter(double radius, double *diameter)
{
    if (diameter == NULL || !isfinite(radius) ||
        radius < 0.0 || radius > DBL_MAX / 2.0) {
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

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        char *new_input;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            fputs("Input is too large.\n", stderr);
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    fputs("Input is too large.\n", stderr);
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                goto cleanup;
            }

            input = new_input;
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

    if (capacity <= length) {
        char *new_input;

        if (length == SIZE_MAX) {
            fputs("Input is too large.\n", stderr);
            goto cleanup;
        }

        new_input = realloc(input, length + 1);
        if (new_input == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            goto cleanup;
        }

        input = new_input;
    }

    input[length] = '\0';

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid radius.\n", stderr);
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || calculate_diameter(radius, &diameter) != 0) {
        fputs("Invalid radius.\n", stderr);
        goto cleanup;
    }

    if (printf("%.10g\n", diameter) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}