#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

double complex_angle(double real, double imag) {
    if (real == 0.0 && imag == 0.0) {
        errno = EDOM;
        return 0.0;
    }
    return atan2(imag, real);
}

static void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    if (ferror(stdin)) {
        clearerr(stdin);
    }
}

static bool read_and_validate_double(const char *prompt, double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[257];
    char *endptr;
    size_t len;

    memset(input, 0, sizeof(input));

    printf("%s", prompt);
    if (fgets(input, (int)sizeof(input) - 1, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return false;
    }
    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        clear_input_buffer();
        fprintf(stderr, "Input too long.\n");
        return false;
    }
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    errno = 0;
    *value = strtod(input, &endptr);
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range.\n");
        return false;
    }
    if (endptr == input) {
        fprintf(stderr, "Invalid number format.\n");
        return false;
    }
    while (*endptr != '\0') {
        if (*endptr != ' ' && *endptr != '\t') {
            fprintf(stderr, "Invalid characters in input.\n");
            return false;
        }
        endptr++;
    }

    return true;
}

int main(void) {
    double real, imag, angle;

    if (!read_and_validate_double("Enter real part: ", &real)) {
        return EXIT_FAILURE;
    }

    if (!read_and_validate_double("Enter imaginary part: ", &imag)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    angle = complex_angle(real, imag);
    if (errno == EDOM) {
        fprintf(stderr, "Angle undefined for zero complex number.\n");
        return EXIT_FAILURE;
    }

    printf("Angle: %f radians\n", angle);
    return EXIT_SUCCESS;
}