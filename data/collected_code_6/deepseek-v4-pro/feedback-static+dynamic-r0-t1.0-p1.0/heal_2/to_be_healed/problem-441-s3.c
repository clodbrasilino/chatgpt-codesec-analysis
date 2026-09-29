#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

double cube_surface_area(double side_length) {
    if (side_length <= 0) {
        return -1.0;
    }
    return 6.0 * side_length * side_length;
}

int main(void) {
    double input;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;

    printf("Enter cube side length: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtod(buffer, &endptr);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\t' && *endptr != '\n') {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    double area = cube_surface_area(input);

    if (area < 0) {
        fprintf(stderr, "Side length must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Surface area: %.2f\n", area);
    return EXIT_SUCCESS;
}