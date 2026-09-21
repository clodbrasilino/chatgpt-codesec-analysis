#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>
#include <string.h>

int validate_dimension(double value, const char *name) {
    if (errno == ERANGE || value <= 0.0 || value > DBL_MAX || isnan(value) || isinf(value)) {
        fprintf(stderr, "Error: %s must be a positive finite number.\n", name);
        return 0;
    }
    return 1;
}

double triangular_prism_volume(double base, double height, double length) {
    double volume;

    if (!validate_dimension(base, "base") ||
        !validate_dimension(height, "height") ||
        !validate_dimension(length, "length")) {
        return -1.0;
    }

    if (base > DBL_MAX / height) {
        fprintf(stderr, "Error: base * height overflows.\n");
        return -1.0;
    }

    volume = (base * height * length) / 2.0;

    if (isinf(volume) || isnan(volume)) {
        fprintf(stderr, "Error: Volume calculation overflow.\n");
        return -1.0;
    }

    return volume;
}

int read_double(const char *prompt, double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    char *endptr;
    size_t len;

    printf("%s", prompt);
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input_buffer);
    if (len > 0 && input_buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Error: Input too long.\n");
        return 0;
    }

    errno = 0;
    *value = strtod(input_buffer, &endptr);
    if (endptr == input_buffer || (*endptr != '\0' && *endptr != '\n')) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 0;
    }

    return 1;
}

int main(void) {
    double base, height, length, volume;

    if (!read_double("Enter base of triangular prism: ", &base)) {
        return EXIT_FAILURE;
    }

    if (!read_double("Enter height of triangular prism: ", &height)) {
        return EXIT_FAILURE;
    }

    if (!read_double("Enter length of triangular prism: ", &length)) {
        return EXIT_FAILURE;
    }

    volume = triangular_prism_volume(base, height, length);
    if (volume < 0.0) {
        return EXIT_FAILURE;
    }

    printf("Volume of triangular prism: %.6f\n", volume);

    return EXIT_SUCCESS;
}