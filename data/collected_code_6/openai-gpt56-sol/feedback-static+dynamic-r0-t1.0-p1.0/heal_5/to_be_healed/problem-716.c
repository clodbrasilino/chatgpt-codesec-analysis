#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 256

static int rhombus_perimeter(double side, double *perimeter)
{
    if (perimeter == NULL || !isfinite(side) ||
        side <= 0.0 || side > DBL_MAX / 4.0) {
        return -1;
    }

    *perimeter = 4.0 * side;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    char *end;
    double side;
    double perimeter;
    size_t length;

    printf("Enter the side length of the rhombus: ");
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    length = strnlen(input, sizeof input);

    if (length == 0 || length == sizeof input) {
        fprintf(stderr, "Invalid side length.\n");
        return EXIT_FAILURE;
    }

    if (input[length - 1] != '\n' && !feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid side length.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || rhombus_perimeter(side, &perimeter) != 0) {
        fprintf(stderr, "Side length must be a finite positive number.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter: %.2f\n", perimeter);
    return EXIT_SUCCESS;
}