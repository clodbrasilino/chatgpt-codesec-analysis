#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

double complex_angle(double real, double imag) {
    if (real == 0.0 && imag == 0.0) {
        errno = EDOM;
        return 0.0;
    }
    return atan2(imag, real);
}

static void clear_input_buffer(void) {
    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
    if (ferror(stdin)) {
        clearerr(stdin);
    }
}

static int read_double(const char *prompt, double *value) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    size_t len;
    int overflow = 0;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 0;
    }

    input[sizeof(input) - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] != '\n') {
        if (len == sizeof(input) - 1) {
            overflow = 1;
            clear_input_buffer();
        }
    } else if (len > 0) {
        input[len - 1] = '\0';
    }

    if (overflow) {
        return 0;
    }

    errno = 0;
    *value = strtod(input, &endptr);
    if (errno == ERANGE || endptr == input || *endptr != '\0') {
        return 0;
    }

    return 1;
}

int main(void) {
    double real, imag, angle;

    if (!read_double("Enter real part: ", &real)) {
        fprintf(stderr, "Invalid real part.\n");
        return EXIT_FAILURE;
    }

    if (!read_double("Enter imaginary part: ", &imag)) {
        fprintf(stderr, "Invalid imaginary part.\n");
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