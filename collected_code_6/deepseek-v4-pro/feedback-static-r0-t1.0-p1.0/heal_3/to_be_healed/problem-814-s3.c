#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <limits.h>

double rhombus_area(double diagonal1, double diagonal2) {
    return (diagonal1 * diagonal2) / 2.0;
}

int main(void) {
    double d1, d2, area;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    size_t len;
    int c;

    printf("Enter first diagonal: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long for first diagonal\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '\0') {
        fprintf(stderr, "Invalid input for first diagonal\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    d1 = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0' || errno == ERANGE || d1 <= 0.0) {
        fprintf(stderr, "Invalid input for first diagonal\n");
        return EXIT_FAILURE;
    }

    printf("Enter second diagonal: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long for second diagonal\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '\0') {
        fprintf(stderr, "Invalid input for second diagonal\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    d2 = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0' || errno == ERANGE || d2 <= 0.0) {
        fprintf(stderr, "Invalid input for second diagonal\n");
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);
    printf("Area of rhombus: %.2f\n", area);

    return EXIT_SUCCESS;
}