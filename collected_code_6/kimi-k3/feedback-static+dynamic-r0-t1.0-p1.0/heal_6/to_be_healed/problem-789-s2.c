#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>

static double calculate_perimeter(int sides, double side_length)
{
    return sides * side_length;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    char *endptr;
    long sides;
    double side_length;
    double perimeter;

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (strchr(input_buffer, '\n') == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) { }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    sides = strtol(input_buffer, &endptr, 10);
    if (errno != 0 || endptr == input_buffer || *endptr != '\n' || sides < 3 || sides > 1000) {
        fprintf(stderr, "Invalid number of sides\n");
        return EXIT_FAILURE;
    }

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (strchr(input_buffer, '\n') == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) { }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    side_length = strtod(input_buffer, &endptr);
    if (errno != 0 || endptr == input_buffer || *endptr != '\n' || side_length <= 0.0 || !isfinite(side_length)) {
        fprintf(stderr, "Invalid side length\n");
        return EXIT_FAILURE;
    }

    perimeter = calculate_perimeter((int)sides, side_length);
    
    if (!isfinite(perimeter)) {
        fprintf(stderr, "Calculation overflow\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", perimeter);
    return EXIT_SUCCESS;
}