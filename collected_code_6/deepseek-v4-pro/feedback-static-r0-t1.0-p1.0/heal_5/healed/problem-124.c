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
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    if (ferror(stdin)) {
        clearerr(stdin);
    }
}

static bool read_and_validate_double(const char *prompt, double *value) {
    char input[257] = {0};
    char *endptr;
    size_t len;

    printf("%s", prompt);
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return false;
    }

    len = strnlen(input, sizeof(input));
    if (len == sizeof(input) - 1 && input[len] == '\0') {
        clear_input_buffer();
        fprintf(stderr, "Input too long.\n");
        return false;
    }
    if (len > 0 && input[len - 1] != '\n') {
        clear_input_buffer();
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
        if (*endptr != '\n' && *endptr != ' ' && *endptr != '\t') {
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