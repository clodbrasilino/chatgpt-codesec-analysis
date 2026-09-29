#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_surface_area(double side, double *area)
{
    if (area == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    if (side > sqrt(DBL_MAX / 6.0)) {
        return -1;
    }

    *area = 6.0 * side * side;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 64;
    int ch;
    char *end;
    double side;
    double area;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity > 4096 / 2) {
                while (ch != '\n' && ch != EOF) {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    ch = fgetc(stdin);
                }
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        free(input);
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid trailing input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (cube_surface_area(side, &area) != 0) {
        fputs("Side length must be finite, nonnegative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}