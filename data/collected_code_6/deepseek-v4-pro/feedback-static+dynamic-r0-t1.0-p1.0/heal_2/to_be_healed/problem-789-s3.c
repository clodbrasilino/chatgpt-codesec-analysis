#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strlen'
 *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
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
    char input_buffer[256];
    int num_sides = 0;
    double side_len = 0.0;
    double perimeter = 0.0;
    char *end_ptr = NULL;
    long parsed_sides = 0;
    size_t len = 0;

    printf("Enter number of sides: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input_buffer);
    if (len == 0 || input_buffer[len - 1] != '\n') {
        if (len >= sizeof(input_buffer) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
        fprintf(stderr, "Invalid input for number of sides.\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    parsed_sides = strtol(input_buffer, &end_ptr, 10);
    if (errno == ERANGE || end_ptr == input_buffer || *end_ptr != '\n') {
        fprintf(stderr, "Invalid input for number of sides.\n");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MIN'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     */
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input_buffer);
    if (len == 0 || input_buffer[len - 1] != '\n') {
        if (len >= sizeof(input_buffer) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
        fprintf(stderr, "Invalid input for side length.\n");
        return EXIT_FAILURE;
    }
    errno = 0;
    side_len = strtod(input_buffer, &end_ptr);
    if (errno == ERANGE || end_ptr == input_buffer || *end_ptr != '\n') {
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