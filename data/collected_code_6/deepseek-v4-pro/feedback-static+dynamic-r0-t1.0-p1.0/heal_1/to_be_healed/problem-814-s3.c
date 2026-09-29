#include <stdio.h>
#include <stdlib.h>

double rhombus_area(double diagonal1, double diagonal2) {
    return (diagonal1 * diagonal2) / 2.0;
}

int main(void) {
    double d1, d2, area;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100];
    char *endptr;

    printf("Enter first diagonal: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    d1 = strtod(input, &endptr);
    if (endptr == input || d1 <= 0) {
        fprintf(stderr, "Invalid input for first diagonal\n");
        return EXIT_FAILURE;
    }

    printf("Enter second diagonal: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    d2 = strtod(input, &endptr);
    if (endptr == input || d2 <= 0) {
        fprintf(stderr, "Invalid input for second diagonal\n");
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);
    printf("Area of rhombus: %.2f\n", area);

    return EXIT_SUCCESS;
}