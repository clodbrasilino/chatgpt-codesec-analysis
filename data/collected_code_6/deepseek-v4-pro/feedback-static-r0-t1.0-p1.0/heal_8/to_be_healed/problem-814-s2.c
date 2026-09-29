#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <stdbool.h>
#include <limits.h>

double rhombus_area(double diagonal1, double diagonal2) {
    if (diagonal1 <= 0 || diagonal2 <= 0) {
        return -1.0;
    }
    if (diagonal1 > DBL_MAX / diagonal2) {
        return -1.0;
    }
    return (diagonal1 * diagonal2) / 2.0;
}

static void clear_input_buffer(void) {
    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static bool read_double(double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    size_t len;

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return false;
    }

    len = strnlen(input, sizeof(input));
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return false;
    }

    if (input[len - 1] != '\n') {
        bool overflow = false;
        if (len >= sizeof(input) - 1) {
            overflow = true;
        }
        clear_input_buffer();
        if (overflow) {
            fprintf(stderr, "Input too long\n");
            return false;
        }
    } else {
        input[len - 1] = '\0';
    }

    char *trimmed = input;
    while (*trimmed == ' ' || *trimmed == '\t') {
        trimmed++;
    }

    if (*trimmed == '\0') {
        fprintf(stderr, "Invalid input\n");
        return false;
    }

    errno = 0;
    *value = strtod(trimmed, &endptr);
    if (endptr == trimmed) {
        fprintf(stderr, "Invalid input\n");
        return false;
    }

    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return false;
    }

    if (errno == ERANGE || *value <= 0) {
        fprintf(stderr, "Value out of range or not positive\n");
        return false;
    }

    return true;
}

int main(void) {
    double d1;
    double d2;
    double area;

    printf("Enter length of first diagonal: ");
    if (!read_double(&d1)) {
        return EXIT_FAILURE;
    }

    printf("Enter length of second diagonal: ");
    if (!read_double(&d2)) {
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);
    if (area < 0) {
        fprintf(stderr, "Diagonals must be positive numbers or values too large\n");
        return EXIT_FAILURE;
    }

    printf("Area of rhombus: %.2f\n", area);
    return EXIT_SUCCESS;
}