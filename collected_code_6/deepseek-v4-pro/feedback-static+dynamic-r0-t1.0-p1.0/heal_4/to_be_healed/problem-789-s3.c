#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

double calculate_polygon_perimeter(int sides, double side_length) {
    if (sides < 3) {
        errno = EINVAL;
        return -1.0;
    }
    if (side_length < 0.0 || !isfinite(side_length)) {
        errno = EINVAL;
        return -1.0;
    }
    if (side_length > DBL_MAX / (double)sides) {
        errno = ERANGE;
        return -1.0;
    }
    return (double)sides * side_length;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[512];
    int num_sides = 0;
    double side_len = 0.0;
    double perimeter = 0.0;
    char *end_ptr = NULL;
    long parsed_sides = 0;
    size_t len = 0;
    /* Possible weaknesses found:
     *  Variable 'c' is assigned a value that is never used. [unreadVariable]
     */
    int c = 0;

    printf("Enter number of sides: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input_buffer, sizeof(input_buffer));
    if (len == 0 || input_buffer[len - 1] != '\n') {
        if (len >= sizeof(input_buffer) - 1) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        } else {
            /* Possible weaknesses found:
             *  Variable 'input_buffer[sizeof(input_buffer)-1]' is assigned a value that is never used. [unreadVariable]
             */
            input_buffer[sizeof(input_buffer) - 1] = '\0';
        }
        fprintf(stderr, "Invalid input for number of sides.\n");
        return EXIT_FAILURE;
    }

    input_buffer[len - 1] = '\0';
    errno = 0;
    parsed_sides = strtol(input_buffer, &end_ptr, 10);
    if (errno == ERANGE || end_ptr == input_buffer || *end_ptr != '\0') {
        fprintf(stderr, "Invalid input for number of sides.\n");
        return EXIT_FAILURE;
    }
    if (parsed_sides < INT_MIN || parsed_sides > INT_MAX) {
        fprintf(stderr, "Invalid input for number of sides.\n");
        return EXIT_FAILURE;
    }
    num_sides = (int)parsed_sides;

    printf("Enter side length: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input_buffer, sizeof(input_buffer));
    if (len == 0 || input_buffer[len - 1] != '\n') {
        if (len >= sizeof(input_buffer) - 1) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        } else {
            /* Possible weaknesses found:
             *  Variable 'input_buffer[sizeof(input_buffer)-1]' is assigned a value that is never used. [unreadVariable]
             */
            input_buffer[sizeof(input_buffer) - 1] = '\0';
        }
        fprintf(stderr, "Invalid input for side length.\n");
        return EXIT_FAILURE;
    }

    input_buffer[len - 1] = '\0';
    errno = 0;
    side_len = strtod(input_buffer, &end_ptr);
    if (errno == ERANGE || end_ptr == input_buffer || *end_ptr != '\0') {
        fprintf(stderr, "Invalid input for side length.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    perimeter = calculate_polygon_perimeter(num_sides, side_len);
    if (errno != 0 || perimeter < 0.0) {
        fprintf(stderr, "Invalid polygon parameters.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter: %.15g\n", perimeter);
    return EXIT_SUCCESS;
}