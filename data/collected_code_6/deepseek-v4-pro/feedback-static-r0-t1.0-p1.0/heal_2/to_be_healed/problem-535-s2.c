#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cylinder_circle_area(double radius) {
    if (radius < 0) {
        return -1.0;
    }
    return M_PI * radius * radius;
}

int main(void) {
    double radius;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    size_t len;

    printf("Enter the radius of the cylinder: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF);
        fprintf(stderr, "Input too long. Please enter a shorter value.\n");
        return EXIT_FAILURE;
    }

    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &endptr);

    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Value out of range.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0) {
        fprintf(stderr, "Radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    double area = cylinder_circle_area(radius);
    printf("The area of the top/bottom surface is: %.6f\n", area);

    return EXIT_SUCCESS;
}