#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <float.h>
#include <math.h>

#define INPUT_BUFFER_SIZE 256

double lateral_surface_area_cuboid(double length, double width, double height) {
    if (length < 0.0 || width < 0.0 || height < 0.0) {
        fprintf(stderr, "Error: Dimensions cannot be negative.\n");
        return -1.0;
    }
    if (length > DBL_MAX / 2.0 || width > DBL_MAX / 2.0 || height > DBL_MAX / 2.0) {
        fprintf(stderr, "Error: Dimensions too large, overflow detected.\n");
        return -1.0;
    }
    double sum = length + width;
    if (sum > DBL_MAX / (2.0 * height)) {
        fprintf(stderr, "Error: Computation would overflow.\n");
        return -1.0;
    }
    return 2.0 * height * sum;
}

int read_dimension(const char *prompt, double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[INPUT_BUFFER_SIZE];
    char *endptr;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    printf("%s", prompt);
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input_buffer);

    if (len > 0 && input_buffer[len - 1] != '\n') {
        if (len == sizeof(input_buffer) - 1) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            fprintf(stderr, "Error: Input too long.\n");
            return 0;
        }
    } else if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Error: Empty input.\n");
        return 0;
    }

    errno = 0;
    *value = strtod(input_buffer, &endptr);

    if (endptr == input_buffer) {
        fprintf(stderr, "Error: Not a valid number.\n");
        return 0;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Error: Trailing characters after number.\n");
        return 0;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Error: Number out of range.\n");
        return 0;
    }

    if (isnan(*value)) {
        fprintf(stderr, "Error: NaN not allowed.\n");
        return 0;
    }

    if (isinf(*value)) {
        fprintf(stderr, "Error: Infinity not allowed.\n");
        return 0;
    }

    return 1;
}

int main(void) {
    double length, width, height;

    if (!read_dimension("Enter length: ", &length)) {
        return EXIT_FAILURE;
    }

    if (!read_dimension("Enter width: ", &width)) {
        return EXIT_FAILURE;
    }

    if (!read_dimension("Enter height: ", &height)) {
        return EXIT_FAILURE;
    }

    double area = lateral_surface_area_cuboid(length, width, height);
    if (area < 0) {
        return EXIT_FAILURE;
    }

    printf("Lateral surface area: %.2f\n", area);
    return EXIT_SUCCESS;
}