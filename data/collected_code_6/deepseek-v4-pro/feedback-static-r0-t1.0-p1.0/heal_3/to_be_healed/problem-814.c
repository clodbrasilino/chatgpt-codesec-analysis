#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 128

double rhombus_area(double diagonal1, double diagonal2) {
    if (diagonal1 <= 0 || diagonal2 <= 0) {
        return -1.0;
    }
    return (diagonal1 * diagonal2) / 2.0;
}

int main(void) {
    double d1, d2, area;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    char *endptr;
    size_t len;

    printf("Enter length of first diagonal: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (input[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    d1 = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter length of second diagonal: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (input[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    d2 = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);
    if (area < 0) {
        fprintf(stderr, "Diagonals must be positive\n");
        return EXIT_FAILURE;
    }

    printf("Area of rhombus: %.2f\n", area);
    return EXIT_SUCCESS;
}